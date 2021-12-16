#pragma once

class BufferValue
{
protected:
    int BUFFERSIZE = -1;

    virtual bool* SubBuffer(bool* buffer, size_t startIndex, size_t count)
	{
		if (startIndex >= BUFFERSIZE  || count < 1 || (count + startIndex > BUFFERSIZE))
			throw invalid_argument("Invalid subbuffer args");

		bool* subBuffer = new bool[count];

		for (size_t i = startIndex, c = 0; i < count + startIndex; i++, c++)
			subBuffer[c] = buffer[i];

		return subBuffer;
	}
	virtual void WriteToBuffer(bool* buffer, bool* subBuffer, size_t startIndex, size_t count)
	{
		for (size_t i = startIndex, c = 0; i < count + startIndex; i++, c++)
			buffer[i] = subBuffer[c];
	}
	virtual void SwapSubBuffers(bool* buffer, size_t startIndex1, size_t startIndex2, size_t count)
	{
		bool* buffer1 = SubBuffer(buffer, startIndex1, count);
		bool* buffer2 = SubBuffer(buffer, startIndex2, count);

		WriteToBuffer(buffer, buffer1, startIndex2, count);
		WriteToBuffer(buffer, buffer2, startIndex1, count);

		delete[] buffer1, buffer2;
	}
	virtual void PrintCustomBuffer(bool* buffer, int count)
	{
		for (size_t i = 0; i < count; i++)
			cout << buffer[i];
		cout << "\n";
	}
};