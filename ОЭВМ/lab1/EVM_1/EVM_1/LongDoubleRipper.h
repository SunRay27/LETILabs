#pragma once

class LongDoubleRipper : BufferValue
{
	
public:
	LongDoubleRipper()
	{
		BUFFERSIZE = sizeof(long double) * 8;//define long double size
	}
	/// <summary>
	/// print long double bits info
	/// </summary>
	/// <param name="inputDouble"></param>
	void PrintBits(long double inputDouble)
	{
		bool* buffer = new bool[BUFFERSIZE];
		ToBuffer(buffer, inputDouble);

		cout << "read value:\n";
		PrintBuffer(buffer);

		delete[] buffer;
	}
	/// <summary>
	/// swaps 2 bit groups within long double
	/// </summary>
	/// <param name="value">input long double</param>
	/// <param name="startIndex1">first bit group start index</param>
	/// <param name="startIndex2">second bit group start index</param>
	/// <param name="count">size of both bit groups</param>
	void SwapBitGroups(long double value, int startIndex1, int startIndex2, int count)
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

		delete[] buffer, buffer1, buffer2;
	}

private:
	/// <summary>
	/// get int value from buffer contents
	/// </summary>
	/// <param name="buf">buffer pointer</param>
	/// <returns></returns>
	long double FromBuffer(bool* buf)
	{
		long long result = 0;
		for (size_t i = 0; i < BUFFERSIZE; i++)
			if (buf[i] != 0)
				result = result | (1LL << (BUFFERSIZE - i - 1));

		LongDoubleUnion u;
		u.long_int = result;
		return u.long_double;
	}
	/// <summary>
	/// convert fill buffer with long double bits
	/// </summary>
	/// <param name="buf">buffer pointer</param>
	/// <param name="inputDouble">long double to fill from</param>
	void ToBuffer(bool* buf, long double inputDouble)
	{
		LongDoubleUnion u;
		u.long_double = inputDouble;

		for (int bitNumber = BUFFERSIZE - 1; bitNumber >= 0; bitNumber--)
		{
			long long compareInt = 1LL << bitNumber;
			buf[BUFFERSIZE - 1 - bitNumber] = (u.long_int & compareInt) != 0 ? 1 : 0;
		}

	}
	void PrintBuffer(bool* buf)
	{
		cout << buf[0];

		cout << " ";
		for (size_t i = 1; i < 12; i++)
			cout << buf[i];

		cout << " ";
		for (size_t i = 12; i < BUFFERSIZE; i++)
			cout << buf[i];
		cout << "\n";
	}
	union LongDoubleUnion
	{
		long double long_double;
		long long long_int;
	};
};

