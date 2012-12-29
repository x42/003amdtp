doubleOhThree - amdtp
---------------------

Reverse engineered AMDTP ISO stream en/decoding for the Digidesign(TM) 003R.


AMDTP is the Audio & Music Data Transmission Protocol. It is used on top of
IEEE 1394 (aka Firewire) to provide communication between a computer and sound-card.

The Digidesign 003R uses a slight modification of the standard data stream format.
It obfuscates the audio-data in the ISO-stream. Specifically it distributes the
middle byte of the 24bit data stream across neighboring or all channels.

Playing a standard ISO-stream will add *hissing* noise to the audio.

The goal of this project is to provide a free/libre software solution to the
encoding used by the Digidesign(TM) 003R. Integration into the ALSA subsystem
of Linux is currently being worked on.

The code has been tested to work with 003R (rack mount). It is currently
unknown if the same mechanism is used for other Digidesign devices.


Excerpt from `sound/firewire/amdtp.c`:

<pre>
static void amdtp_write_samples(struct amdtp_stream *s,
				struct snd_pcm_substream *pcm,
				__be32 *buffer, unsigned int frames)
{
	struct snd_pcm_runtime *runtime = pcm->runtime;
	unsigned int channels, remaining_frames, frame_step, i, c;
	const u32 *src;

	channels = s->pcm_channels;
	src = (void *)runtime->dma_area +
			s->pcm_buffer_pointer * (runtime->frame_bits / 8);
	remaining_frames = runtime->buffer_size - s->pcm_buffer_pointer;
	frame_step = s->data_block_quadlets;

	for (i = 0; i < frames; ++i) {
		for (c = 0; c < channels; ++c) {
			buffer[s->pcm_quadlets[c]] =
					cpu_to_be32((*src >> 8) | 0x40000000);
			src++;
		}

		digi_encode(&buffer[s->pcm_quadlets[0]], channels); ///< hook to 003amdtp

		buffer += frame_step;
		if (--remaining_frames == 0)
			src = (void *)runtime->dma_area;
	}
}
</pre>

003amdtp is licensed in terms of the GNU General Public License Version 2 or later.
