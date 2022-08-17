# C++ Wave File Reader
A simple WAVE file reader in C++. It reads in the necessary audio data from a provided path to a `.wav` file.

Example usage with OpenAL:

`
Wave wave("foo/bar/baz.wav");

...

alBufferData(buffer, AL_FORMAT_STEREO16, asc.GetData(), asc.GetDataSize(), asc.GetSampleRate());

`

Note that you can easily figure out the correct format by using `wave.GetNumChannels()` which returns the number of channels,
and `wave.GetBPS()` which returns the bits per sample.
