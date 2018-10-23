#include <fstream>
const float f = 3.14f;
int main(){
std::ofstream ofile("foobar.bin", std::ios::binary);
ofile.write((char*) &f, sizeof(float));
return 0;
}
