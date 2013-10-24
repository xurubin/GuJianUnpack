unsigned int ChangeEndianess(unsigned int x);

class CFileDecrypter
{
public:
	void SetKey(char* FileKey, int KeyLen);
	int Decrypt(char* dst, char * src, int len, int type);
private:
	char filekey[0x110];
	int derivedkey[5];
};


class CDecompresser
{
	static int decompress(char* src, char* dst, int len);
};
int deflate1(char* src, char* dst, int len);
int deflate2(char* src, char* dst, int len);
