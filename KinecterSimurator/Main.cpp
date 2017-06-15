//siv3dシリアル通信サンプルプログラム
#include <Siv3D.hpp>
#include "Kinecter.h"

void Main()
{
	Kinecter* k = new Kinecter();
	k->Run();
	delete(k);
}
