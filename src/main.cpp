#include "judge.h"
#include "Functions_Linux.h"
#include <cstdlib>
using namespace std;

int main(int argc,char *argv[]) {
	Contest x;
	if (JudgeSettings::ReadFromArgv(argc,argv))
		return 0;
	x.InitContest();
	x.InitSPJ();
	JudgeSettings::ReadSettings(GetJudgerc().c_str());
	JudgeSettings::ReadSettings("judgerc");
	x.JudgeContest();
	ClearFile();
	JudgeOutput::OutputContest(x);
	JudgeOutput::ConverttoCSV(x,"result.csv");
    return 0;
}
