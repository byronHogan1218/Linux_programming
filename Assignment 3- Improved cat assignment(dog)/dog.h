//header file
#ifndef DOG_H
#define DOG_H
//programmed by byron hogan
//z1825194
class dog{
	public:
	void cipher(char [],int&,int);
	void rotate(char[],int&,int);
	void hexa(char[], int,int);


	private:
	char* buffer;
	void convertToHex(int,char[]);
};
#endif
