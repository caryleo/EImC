#pragma once
#ifndef MODEWHILE_H_
#define MODEWHILE_H_
class ModeWhile {
public:
	ModeWhile(int _s, int _t, int _x, int _y);
	bool calcu();
	int runWhile();
	int conTop, conBottom, top, bottom;

};

class ModeDo {
public:
	ModeDo(int _s, int _t, int _x, int _y);
	bool calcu();
	int runDo();
	int conTop, conBottom, top, bottom;
};
#endif //!MODEWHILE_H_



