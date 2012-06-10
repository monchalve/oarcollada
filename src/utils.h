/* 

	Helper functions 
	
*/

#include <cstddef>
#include <string>

namespace OARCollada {

using namespace std;
	
class Utils {
public:
	static void reverse(char bytes[], size_t size) {
		for (size_t i = 0; i < size/2; i++) {
			char temp = bytes[i];
			size_t end = size - i -1;
			bytes[i] = bytes[end];
			bytes[end] = temp;
			end--;
		}
	}
	
	static float toSingle(char bytes[], int pos) {
		
		unsigned int a1 = ((unsigned int)bytes[0] << 24);
		unsigned int a2 = ((unsigned int)bytes[1] << 16);
		unsigned int a3 = ((unsigned int)bytes[2] << 8);
		unsigned int a4 = ((unsigned int)bytes[3]);
		
		return (float) (a1 | a2 | a3 | a4);
	}
	
	static bool isBigEndian() {
		long x = 0x34333231;
		char *y = (char *) &x;
		return (strncmp(y,"1234",4));
	}

	static char swapWords(char value)
	{
    	return (char)(((value & 0xF0) >> 4) | ((value & 0x0F) << 4));
	}
	
	static char* floatToBytes(float f) {
		char *bytes = (char *)malloc(sizeof(char) * 4);
		memcpy(bytes, &f, 4*sizeof(char));
		
		if (isBigEndian()) {
			reverse(bytes, 4);
		}
		
		return bytes;
	}
	
	static float bytesToFloat(char bytes[], int pos)
    {
        if (isBigEndian())
        {
			char newBytes[4];
            memcpy(newBytes, bytes + pos, 4 * sizeof(char));
            reverse(newBytes, 4);
            return toSingle(newBytes, 0);
        }
        else
        {
            return toSingle(bytes, pos);
        }
    }
    
};
	
}