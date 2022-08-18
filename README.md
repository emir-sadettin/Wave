# C++ Wave File Reader
A simple WAVE file reader in C++. It reads in the necessary audio data from a provided path to a `.wav` file.

## Usage
You do not need to build anything, just copy the header and source file into your project making sure they are in
the same folder and it should work.

Example:
```
Wave wave("foo/bar/baz.wav");
...
alBufferData(buffer, AL_FORMAT_STEREO16, asc.GetData(), asc.GetDataSize(), asc.GetSampleRate());
```
Please note that there are extra methods provided in the `Wave` class to get the number of channels and the *bits per sample*
in case you need them.

## Notes

I made this loader for one main reason. In my experience, certain `.wav` files do not follow the **Canonical** format provided below:

![alt text](https://e2e.ti.com/cfs-file/__key/communityserver-blogs-components-weblogfiles/00-00-00-07-62/Canonical-WAVE-file-format.jpg)

Sometimes, there are extra subchunks between the *fmt* and *data* headers, often the *LIST* subchunks as
pointed out here: https://stackoverflow.com/questions/63929283/what-is-a-list-chunk-in-a-riff-wav-header

Many of the `.wav` readers I have tried do not take care of this information, and it took me a while to figure out why
my program was not working as expected.

I hope this is as helpful to you as it was to me.
