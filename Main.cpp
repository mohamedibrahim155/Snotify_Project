
#include "Utils/List.h"
#include "Snotify/cMusicGenerator.h"
int main()
{
	List<int> test;

	test.Add(10);
	test.Add(20);
	test.Add(30);
	test.Add(20);
	test.Add(20);

	for (size_t i = 0; i < test.GetLength(); i++)
	{
		std::cout << " Add : " << test[2] << std::endl;
	}
 
  test.Remove(20);
  test.Remove(20);
  for (size_t i = 0; i < test.GetLength(); i++)
  {
	  std::cout << "i : " << test[i] << std::endl;
  }

	return 0;
}