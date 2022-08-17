#include <iostream>
#include <string>

class Wave
{
	struct BinaryInfo
	{
		std::string d0;
		std::string d1;
		std::string d2;
		std::string d3;
	};

	BinaryInfo GetInfo(char data[4]);
private:
	uint32_t Char4ToUint32BigEndian(char data[4]);
	uint32_t Char4ToUint32LittleEndian(char data[4]);

	uint16_t Char2ToUint16BigEndian(char data[2]);
	uint16_t Char2ToUint16LittleEndian(char data[2]);

private:
	uint32_t sampleRate;
	uint32_t dataSize;

	uint16_t numChannels;
	uint16_t bitsPerSample;

	char* data;
public:
	Wave(const std::string& path);

	uint16_t GetNumChannels() const;
	uint16_t GetBPS() const;
	uint32_t GetSampleRate() const;
	uint32_t GetDataSize() const;

	char* GetData() const;

	~Wave();
};