# C++ Wave File Reader
A simple WAVE file reader in C++. It reads in the necessary audio data from a provided path to a `.wav` file.
Example usage with OpenAL:
```
Wave asc("../AudioEngine/tick.wav");
...
alBufferData(buffer, AL_FORMAT_STEREO16, asc.GetData(), asc.GetDataSize(), asc.GetSampleRate());
```

This also solves the problem of certain `.wav` files having a LIST subchunks.
