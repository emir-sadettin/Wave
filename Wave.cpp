#include <iostream>
#include <fstream>
#include <cstring>
#include <bitset>

#include "Wave.h"

Wave::BinaryInfo Wave::GetInfo(char data[4])
{
    std::string d0 = std::bitset<8>(data[0]).to_string();
    std::string d1 = std::bitset<8>(data[1]).to_string();
    std::string d2 = std::bitset<8>(data[2]).to_string();
    std::string d3 = std::bitset<8>(data[3]).to_string();

    return { d0, d1, d2, d3 };
}

uint32_t Wave::Char4ToUint32BigEndian(char data[4])
{
    BinaryInfo info = GetInfo(data);

    std::bitset<32> result(info.d0 + info.d1 + info.d2 + info.d3);
    return (uint32_t) result.to_ulong();
}

uint32_t Wave::Char4ToUint32LittleEndian(char data[4])
{
    BinaryInfo info = GetInfo(data);

    std::bitset<32> result(info.d3 + info.d2 + info.d1 + info.d0);
    return (uint32_t) result.to_ulong();
}

uint16_t Wave::Char2ToUint16BigEndian(char data[2])
{
    BinaryInfo info = GetInfo(data);

    std::bitset<16> result(info.d1 + info.d0);
    return (uint16_t) result.to_ulong();
}

uint16_t Wave::Char2ToUint16LittleEndian(char data[2])
{
    BinaryInfo info = GetInfo(data);

    std::bitset<16> result(info.d0 + info.d1);
    return (uint16_t) result.to_ulong();
}

Wave::Wave(const std::string& path)
{
    std::ifstream file(path, std::ios::binary);
    char info[5] = {};

    file.read(info, 4); // RIFF
    file.read(info, 4); // Chunk size

    file.read(info, 4); // WAVE
    file.read(info, 4); // Subchunk 1 ID
    file.read(info, 4); // Subchunk 1 size
    file.read(info, 2); // Audio format
    file.read(info, 2); // Channels

    numChannels = Char2ToUint16BigEndian(info);

    file.read(info, 4); // Sample rate

    sampleRate = Char4ToUint32LittleEndian(info);

    file.read(info, 4); // Byte rate
    file.read(info, 2); // Block align
    file.read(info, 2); // Bits per sample

    bitsPerSample = Char2ToUint16BigEndian(info);

    file.read(info, 4); // Subchunk 2 ID (Not necessarily the 'data' chunk)
    std::string chunkName = info;

    file.read(info, 4); // Subchunk 2 size
    uint32_t chunkSize = Char4ToUint32LittleEndian(info);

    while (chunkName != "data")
    {
        // Skip entire chunk
        for (uint32_t i = 0; i < (chunkSize / 2); i++)
            file.read(info, 2);

        file.read(info, 4);
        chunkName = std::string(info);
    }
    
    file.read(info, 4); // 'data' chunk size

    dataSize = Char4ToUint32LittleEndian(info);
    data = new char[dataSize];

    file.read(data, dataSize); // Actual audio data
    file.close();
}

uint16_t Wave::GetNumChannels() const
{
    return numChannels;
}

uint16_t Wave::GetBPS() const
{
    return bitsPerSample;
}

uint32_t Wave::GetSampleRate() const
{
    return sampleRate;
}

uint32_t Wave::GetDataSize() const
{
    return dataSize;
}

char* Wave::GetData() const
{
    return data;
}

Wave::~Wave()
{
    delete[] data;
}
