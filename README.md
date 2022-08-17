# C++ Wave File Reader
A simple WAVE file reader in C++. It reads in the necessary audio data from a provided path to a `.wav` file.
Example usage with OpenAL:
```
Wave asc("foo/bar/baz.wav");
...
alBufferData(buffer, AL_FORMAT_STEREO16, asc.GetData(), asc.GetDataSize(), asc.GetSampleRate());
```

This also solves the problem of certain `.wav` files having a LIST subchunk as
pointed out here: https://stackoverflow.com/questions/63929283/what-is-a-list-chunk-in-a-riff-wav-header
