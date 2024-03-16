#pragma once

#include <array>

#include "Location.h"

static const char MAX_REGION_INDEX = 23;

static const char* rawRegion =
"EEEEE@@@@@@@@@@@@@@@@@WWWWWWWWWW@@@BBBBBBBBBB@@@@@@@@@@@@@@@@@TTTTTTTTTT@@@DDDDDDDDDD@@@@@@@@@@@@@@@@@VVVVVVVVVV@@@EEEEE"
"EEEEEE@@@@@@@KKKKK@@@@@@WWWWWWWWW@@@BBBBBBBBBB@@@@@@@HHHHH@@@@@@TTTTTTTTT@@@DDDDDDDDDD@@@@@@@JJJJJ@@@@@@VVVVVVVVV@@@EEEE"
"EEEEEE@@@@@@KKKKKKKK@@@@@WWWWWWWW@@@BBBBBBBBBB@@@@@@HHHHHHHH@@@@@TTTTTTTT@@@DDDDDDDDDD@@@@@@JJJJJJJJ@@@@@VVVVVVVV@@@EEEE"
"EEEE@@@@@@KKKKKKKKKKKK@@@@WWWWWWW@@@BBBBBBBB@@@@@@HHHHHHHHHHHH@@@@TTTTTTT@@@DDDDDDDD@@@@@@JJJJJJJJJJJJ@@@@VVVVVVV@@@EEEE"
"EEE@@@@@@KKKKKKKKKKKKKK@@@@WWWWWW@@@BBBBBBB@@@@@@HHHHHHHHHHHHHH@@@@TTTTTT@@@DDDDDDD@@@@@@JJJJJJJJJJJJJJ@@@@VVVVVV@@@EEEE"
"E@@@@@@@KKKKKKKKKKKKKKKK@@@WWWWWW@@@BBBBB@@@@@@@HHHHHHHHHHHHHHHH@@@TTTTTT@@@DDDDD@@@@@@@JJJJJJJJJJJJJJJJ@@@VVVVVV@@@EEEE"
"EKKK@@@KKKKKKKKKKKKKKKKK@@@WWWWWW@@@@BBBBHHH@@@HHHHHHHHHHHHHHHHH@@@TTTTTT@@@@DDDDJJJ@@@JJJJJJJJJJJJJJJJJ@@@VVVVVV@@@@EEE"
"KKKKKKKKKKKKKKKKKKKKKKKKK@@@WWWWW@@@@@HHHHHHHHHHHHHHHHHHHHHHHHHHH@@@TTTTT@@@@@JJJJJJJJJJJJJJJJJJJJJJJJJJJ@@@VVVVV@@@@@KK"
"KKKKKKKKKKKKKKKKKKKKKKKKK@@@@WWWQQ@@@@HHHHHHHHHHHHHHHHHHHHHHHHHHH@@@@TTTNN@@@@JJJJJJJJJJJJJJJJJJJJJJJJJJJ@@@@VVVPP@@@@KK"
"KKKKKKKKKKKKKKKKKKKKKKKKK@@@@@QQQQQQ@HHHHHHHHHHHHHHHHHHHHHHHHHHHH@@@@@NNNNNN@JJJJJJJJJJJJJJJJJJJJJJJJJJJJ@@@@@PPPPPP@KKK"
"KKKKKKKKKKKKKKKKKKKKKKKKKK@@@@QQQQQQQHHHHHHHHHHHHHHHHHHHHHHHHHHHHH@@@@NNNNNNNJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ@@@@PPPPPPPKKK"
"KKKKKKKKKKKKKKKKKKKKKKKKKKQQQQQQQQQQQQQHHHHHHHHHHHHHHHHHHHHHHHHHHHNNNNNNNNNNNNNJJJJJJJJJJJJJJJJJJJJJJJJJJJPPPPPPPPPPPPPK"
"KKKKKKKKKKKKKKKKKKKKKKKQQQQQQQQQQQQQQQQQHHHHHHHHHHHHHHHHHHHHHHHNNNNNNNNNNNNNNNNNJJJJJJJJJJJJJJJJJJJJJJJPPPPPPPPPPPPPPPPP"
"PKKKKKKKKKKKKKKK@@KKQQQQQQQQQQQQQQQQQQQQQHHHHHHHHHHHHHHH@@HHNNNNNNNNNNNNNNNNNNNNNJJJJJJJJJJJJJJJ@@JJPPPPPPPPPPPPPPPPPPPP"
"PPPKKKKKKKKKKKKK@@@QQQQQQQQQQQQQQQQQQQQQQQQHHHHHHHHHHHHH@@@NNNNNNNNNNNNNNNNNNNNNNNNJJJJJJJJJJJJJ@@@PPPPPPPPPPPPPPPPPPPPP"
"PPPP@@KKKKKKKKK@@@@@QQQQQQQQQQQQQQQQQQQQQQQQ@@HHHHHHHHH@@@@@NNNNNNNNNNNNNNNNNNNNNNNN@@JJJJJJJJJ@@@@@PPPPPPPPPPPPPPPPPPPP"
"PP@@@@@@@KKKKK@@@@@QQQQQQQQQQQQQQQQQQQQQQQ@@@@@@@HHHHH@@@@@NNNNNNNNNNNNNNNNNNNNNNN@@@@@@@JJJJJ@@@@@PPPPPPPPPPPPPPPPPPPPP"
"@@@@@@@@@@@@@@@@@FFFQQQQQQQQQQQQQQQQQQQ@@@@@@@@@@@@@@@@@@CCCNNNNNNNNNNNNNNNNNNN@@@@@@@@@@@@@@@@@@AAAPPPPPPPPPPPPPPPPPPP@"
"@@@@SSS@@@@@@@@FFFFFFQQQQQQQQQQQQQQQQQ@@@@@@XXX@@@@@@@@CCCCCCNNNNNNNNNNNNNNNNN@@@@@@UUU@@@@@@@@AAAAAAPPPPPPPPPPPPPPPPP@@"
"@@SSSSSSSS@@@@FFFFFFFFQQQQQQQQQQQQQQQ@@@@@XXXXXXXX@@@@CCCCCCCCNNNNNNNNNNNNNNN@@@@@UUUUUUUU@@@@AAAAAAAAPPPPPPPPPPPPPPP@@@"
"SSSSSSSSSSS@@@FFFFFFF@@@QQQQQQQQQQQQ@@@@XXXXXXXXXXX@@@CCCCCCC@@@NNNNNNNNNNNN@@@@UUUUUUUUUUU@@@AAAAAAA@@@PPPPPPPPPPPP@@@@"
"SSSSSSSSSSS@@@FFFFFFFF@@@QQQQQQQQQQQ@@@XXXXXXXXXXXX@@@CCCCCCCC@@@NNNNNNNNNNN@@@UUUUUUUUUUUU@@@AAAAAAAA@@@PPPPPPPPPPP@@@S"
"SSSSSSSSSSS@@@@FFFFFFFF@@@@@QQQQQ@@@@@@@XXXXXXXXXXX@@@@CCCCCCCC@@@@@NNNNN@@@@@@@UUUUUUUUUUU@@@@AAAAAAAA@@@@@PPPPP@@@@@@@"
"@SSSSSSSSSSS@@@FFFFFFFFF@@@@@@@@@@@@@@@@@XXXXXXXXXXX@@@CCCCCCCCC@@@@@@@@@@@@@@@@@UUUUUUUUUUU@@@AAAAAAAAA@@@@@@@@@@@@@@@@"
"@@SSSSSSSSSS@@@FFFFFFFFFF@@@@@@@@@@@@@@@@@XXXXXXXXXX@@@CCCCCCCCCC@@@@@@@@@@@@@@@@@UUUUUUUUUU@@@AAAAAAAAAA@@@@@@@@@@@@@@@"
"@@@@SSSSSSSSS@@@FFFFFFFFFF@@@@@@@LLLLL@@@@@@XXXXXXXXX@@@CCCCCCCCCC@@@@@@@IIIII@@@@@@UUUUUUUUU@@@AAAAAAAAAA@@@@@@@GGGGG@@"
"@@@@@SSSSSSSS@@@FFFFFFFFFF@@@@@@LLLLLLLL@@@@@XXXXXXXX@@@CCCCCCCCCC@@@@@@IIIIIIII@@@@@UUUUUUUU@@@AAAAAAAAAA@@@@@@GGGGGGGG"
"GG@@@@SSSSSSS@@@FFFFFFFF@@@@@@LLLLLLLLLLLL@@@@XXXXXXX@@@CCCCCCCC@@@@@@IIIIIIIIIIII@@@@UUUUUUU@@@AAAAAAAA@@@@@@GGGGGGGGGG"
"GGG@@@@SSSSSS@@@FFFFFFF@@@@@@LLLLLLLLLLLLLL@@@@XXXXXX@@@CCCCCCC@@@@@@IIIIIIIIIIIIII@@@@UUUUUU@@@AAAAAAA@@@@@@GGGGGGGGGGG"
"GGGG@@@SSSSSS@@@FFFFF@@@@@@@LLLLLLLLLLLLLLLL@@@XXXXXX@@@CCCCC@@@@@@@IIIIIIIIIIIIIIII@@@UUUUUU@@@AAAAA@@@@@@@GGGGGGGGGGGG"
"GGGG@@@SSSSSS@@@@FFFFLLL@@@LLLLLLLLLLLLLLLLL@@@XXXXXX@@@@CCCCIII@@@IIIIIIIIIIIIIIIII@@@UUUUUU@@@@AAAAGGG@@@GGGGGGGGGGGGG"
"GGGGG@@@SSSSS@@@@@LLLLLLLLLLLLLLLLLLLLLLLLLLL@@@XXXXX@@@@@IIIIIIIIIIIIIIIIIIIIIIIIIII@@@UUUUU@@@@@GGGGGGGGGGGGGGGGGGGGGG"
"GGGGG@@@@SSSMM@@@@LLLLLLLLLLLLLLLLLLLLLLLLLLL@@@@XXXRR@@@@IIIIIIIIIIIIIIIIIIIIIIIIIII@@@@UUUOO@@@@GGGGGGGGGGGGGGGGGGGGGG"
"GGGGG@@@@@MMMMMM@LLLLLLLLLLLLLLLLLLLLLLLLLLLL@@@@@RRRRRR@IIIIIIIIIIIIIIIIIIIIIIIIIIII@@@@@OOOOOO@GGGGGGGGGGGGGGGGGGGGGGG"
"GGGGGG@@@@MMMMMMMLLLLLLLLLLLLLLLLLLLLLLLLLLLLL@@@@RRRRRRRIIIIIIIIIIIIIIIIIIIIIIIIIIIII@@@@OOOOOOOGGGGGGGGGGGGGGGGGGGGGGG"
"GGGGGGGMMMMMMMMMMMMLLLLLLLLLLLLLLLLLLLLLLLLLLLRRRRRRRRRRRRRIIIIIIIIIIIIIIIIIIIIIIIIIIIOOOOOOOOOOOOOGGGGGGGGGGGGGGGGGGGGG"
"GGGGGMMMMMMMMMMMMMMMLLLLLLLLLLLLLLLLLLLLLLLRRRRRRRRRRRRRRRRRIIIIIIIIIIIIIIIIIIIIIIIOOOOOOOOOOOOOOOOOGGGGGGGGGGGGGGGGGGGG"
"GGMMMMMMMMMMMMMMMMMMMLLLLLLLLLLLLLLL@@LLRRRRRRRRRRRRRRRRRRRRRIIIIIIIIIIIIIII@@IIOOOOOOOOOOOOOOOOOOOOOGGGGGGGGGGGGGGG@@GG"
"MMMMMMMMMMMMMMMMMMMMMMMLLLLLLLLLLLLL@@@RRRRRRRRRRRRRRRRRRRRRRRRIIIIIIIIIIIII@@@OOOOOOOOOOOOOOOOOOOOOOOOGGGGGGGGGGGGG@@@M"
"MMMMMMMMMMMMMMMMMMMMMMMM@@LLLLLLLLL@@@@@RRRRRRRRRRRRRRRRRRRRRRRR@@IIIIIIIII@@@@@OOOOOOOOOOOOOOOOOOOOOOOO@@GGGGGGGGG@@@@@"
"MMMMMMMMMMMMMMMMMMMMMM@@@@@@@LLLLL@@@@@RRRRRRRRRRRRRRRRRRRRRRR@@@@@@@IIIII@@@@@OOOOOOOOOOOOOOOOOOOOOOO@@@@@@@GGGGG@@@@@M"
"MMMMMMMMMMMMMMMMMMM@@@@@@@@@@@@@@@@@@BBBRRRRRRRRRRRRRRRRRRR@@@@@@@@@@@@@@@@@@DDDOOOOOOOOOOOOOOOOOOO@@@@@@@@@@@@@@@@@@EEE"
"EMMMMMMMMMMMMMMMMM@@@@@@WWW@@@@@@@@BBBBBBRRRRRRRRRRRRRRRRR@@@@@@TTT@@@@@@@@DDDDDDOOOOOOOOOOOOOOOOO@@@@@@VVV@@@@@@@@EEEEE"
"EEMMMMMMMMMMMMMMM@@@@@WWWWWWWW@@@@BBBBBBBBRRRRRRRRRRRRRRR@@@@@TTTTTTTT@@@@DDDDDDDDOOOOOOOOOOOOOOO@@@@@VVVVVVVV@@@@EEEEEE"
"E@@@MMMMMMMMMMMM@@@@WWWWWWWWWWW@@@BBBBBBB@@@RRRRRRRRRRRR@@@@TTTTTTTTTTT@@@DDDDDDD@@@OOOOOOOOOOOO@@@@VVVVVVVVVVV@@@EEEEEE"
"EE@@@MMMMMMMMMMM@@@WWWWWWWWWWWW@@@BBBBBBBB@@@RRRRRRRRRRR@@@TTTTTTTTTTTT@@@DDDDDDDD@@@OOOOOOOOOOO@@@VVVVVVVVVVVV@@@EEEEEE"
"EEE@@@@@MMMMM@@@@@@@WWWWWWWWWWW@@@@BBBBBBBB@@@@@RRRRR@@@@@@@TTTTTTTTTTT@@@@DDDDDDDD@@@@@OOOOO@@@@@@@VVVVVVVVVVV@@@@EEEEE"
"EEEE@@@@@@@@@@@@@@@@@WWWWWWWWWWW@@@BBBBBBBBB@@@@@@@@@@@@@@@@@TTTTTTTTTTT@@@DDDDDDDDD@@@@@@@@@@@@@@@@@VVVVVVVVVVV@@@EEEEE";

constexpr static std::array<std::array<char, 48>, 120> loadRegion() {
	std::array<std::array<char, 48>, 120> region = std::array<std::array<char, 48>, 120>();

	for (size_t i = 0; i < region.size(); i++)
	{
		for (size_t j = 0; j < region[0].size(); j++)
		{
			region[i][j] = rawRegion[i * 120 + j] - 'A';
		}
	}

	return region;
}

constexpr static std::array<std::vector<Location>, MAX_REGION_INDEX> getRegions()
{
	std::array<std::vector<Location>, MAX_REGION_INDEX> regions = std::array<std::vector<Location>, MAX_REGION_INDEX>();
	const std::array<std::array<char, 48>, 120>& regionValues = loadRegion();
	
	for (size_t i = 0; i < regionValues.size(); i++)
	{
		for (size_t j = 0; j < regionValues[0].size(); j++)
		{
			regions[regionValues[i][j]].push_back(Location(i, j));
		}
	}

	return regions;
}