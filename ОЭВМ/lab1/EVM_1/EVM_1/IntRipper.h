#pragma once

class IntRipper : BufferValue
{
public:
	IntRipper()
	{
		BUFFERSIZE = sizeof(int) * 8; //define int size
	}
	/// <summary>
	/// print integer bits info
	/// </summary>
	/// <param name="inputInt"></param>
	void PrintBits(int inputInt)
	{
		//create buffer for binary representation
		bool* buffer = new bool[BUFFERSIZE];
		ToBuffer(buffer, inputInt);

		//print buffer value
		cout << "read value:\n";
		PrintBuffer(buffer);

		//if value < 0 then convert from two's-complement form to one's-complement form
		if (inputInt < 0)
		{
			TwoToOneComplementForm(buffer);
			cout << "ones' complement form\n";
			PrintBuffer(buffer);
		}

		delete[] buffer;
	}
	/// <summary>
	/// swaps 2 bit groups within integer
	/// </summary>
	/// <param name="value">input integer</param>
	/// <param name="startIndex1">first bit group start index</param>
	/// <param name="startIndex2">second bit group start index</param>
	/// <param name="count">size of both bit groups</param>
	void SwapBitGroups(int value, int startIndex1, int startIndex2, int count)
	{
		bool* buffer = new bool[BUFFERSIZE];
		ToBuffer(buffer, value);

		cout << "original value: ";
		PrintBuffer(buffer);

		//get bit groups as arrays
		bool* buffer1 = SubBuffer(buffer, startIndex1, count);
		bool* buffer2 = SubBuffer(buffer, startIndex2, count);

		//swap bit groups in main buffer
		WriteToBuffer(buffer, buffer1, startIndex2, count);
		WriteToBuffer(buffer, buffer2, startIndex1, count);

		cout << "bit group1: ";
		PrintCustomBuffer(buffer1, count);
		cout << "bit group2: ";
		PrintCustomBuffer(buffer2, count);



		cout << "swap result: ";
		PrintBuffer(buffer);
		cout << "value: " << FromBuffer(buffer) << "\n";
		cout << "one's complement form: ";
		TwoToOneComplementForm(buffer);
		PrintBuffer(buffer);
		cout << "\n";

		delete[] buffer, buffer1, buffer2;
	}

private:
	/// <summary>
	/// Reverses negative value buffer
	/// </summary>
	/// <param name="buf">buffer pointer</param>
	void ReverseNegative(bool* buf)
	{
		for (int i = 0; i < BUFFERSIZE; i++)
			buf[i] = buf[i] == 1 ? 0 : 1;

		//make sure first bit is 1
		buf[0] = 1;
	}
	/// <summary>
	/// convert buffer from two's-complement form to one's-complement form
	/// </summary>
	/// <param name="buf">buffer pointer</param>
	void TwoToOneComplementForm(bool* buf)
	{
		ReverseNegative(buf);
		int reversedInt = FromBuffer(buf);
		int tobuf = reversedInt + 1;
		ToBuffer(buf, tobuf);
	}
	/// <summary>
	/// get int value from buffer contents
	/// </summary>
	/// <param name="buf">buffer pointer</param>
	/// <returns></returns>
	int FromBuffer(bool* buf)
	{
		int result = 0;
		for (size_t i = 0; i < BUFFERSIZE; i++)
			if (buf[i] != 0)
				result = result | (1 << (BUFFERSIZE - i - 1));
		return result;
	}
	/// <summary>
	/// convert fill buffer with integer bits
	/// </summary>
	/// <param name="buf">buffer pointer</param>
	/// <param name="inputInt">integer to fill from</param>
	void ToBuffer(bool* buf, int inputInt)
	{
		for (int bitNumber = BUFFERSIZE - 1; bitNumber >= 0; bitNumber--)
		{
			int compareInt = 1 << bitNumber;
			buf[BUFFERSIZE - 1 - bitNumber] = (inputInt & compareInt) != 0 ? 1 : 0;
		}
	}
	void PrintBuffer(bool* buf)
	{
		for (size_t i = 0; i < BUFFERSIZE; i++)
			cout << buf[i];
		cout << "\n";
	}
};