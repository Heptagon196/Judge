#ifndef LANG
#define LANG
#include "../judge.h"
#include "../ConverttoString.h"
#include "../MultiCompiler.h"
#include <sstream>
#include <iostream>
using namespace std;

static JudgeSettings config;
static void InitLang(JudgeSettings& settings) {
    config = settings;
}

namespace Context {
	static string CUIhelp = "tab: switch modes|'w''s': move|'a''d': turn page|enter: confirm|'q': quit";
	static void PrintHelp() {
		string help =
"Usage:judge [Options]...\n\
This program can judge an OI contest. It compiles codes in directory ./ and source/[Contestant name], and uses the data in directory ./ and data/[Problem name] automatically to judge. It also checks whether freopen is used.\n\
When you run this program as root, it will automatically use chroot to run programs as a simple sandbox.\n\
It searches for invalid functions or headers in C and C++\n\
It uses these commands to compile:\n";
		for (int i = 0; i < Compiler.size(); i++) {
            if (!((Compiler[i].cmd.length() >= strlen("judge")) && (Compiler[i].cmd.substr(0, strlen("judge")) == (string)"judge"))) {
                help+=Compiler[i].cmd+"\n";
            }
        }
		help+="\n\
    -f [STRING]               Forbidden functions in sources\n\
    -f[NUMBER] [STRING]...    [NUMBER] forbidden functions in sources\n\
    -h [STRING]               Forbidden headers in sources\n\
    -h[NUMBER] [STRING]...    [NUMBER] forbidden headers in sources\n\
    -t [TIME]                 Limit time (" + CTS::DoubleToString(config.Default_timelimit) + "s by default)\n\
    -m [MEMORY]               Limit memory (" + CTS::IntToString(config.Default_memorylimit) + "KB by default)\n\
    --csv                     Output result to result.csv after judging. Used by default when there is more than one contestant\n\
    --nocsv                   Turn off csv output(even if there is more than one contestant)\n\
    -c, --cli                 Use a simple CLI to manage a contest\n\
    -o                        Add -O2 option when compiling\n\
    -g                        Generate default judge.conf\n\
    -s                        Execute a script\n\
    --help                    Print this help message and exit\n\
\n\
Global config:\n\
This program will read settings from ~/.judgerc and ./judge.conf. The format is :[Option]([Value1],[Value2]...) Options below are supported:\n\
  Options with no arguments:\n\
    quit                      See 'enter'\n\
  With one argument:\n\
    background, bg            Set the background when print WA,AC,etc. : black green red blue yellow cyan white purple\n\
    FileIO, file              Use file input/output forcibly; 'true' or 'false'\n\
    O2, optimize              Add -O2 option when compiling; 'true' or 'false'\n\
	enter                     Start to configurate the problem specified, use the rule of problem config file to analyse the command below, end with command 'quit'\n\
  With two arguments:\n\
    SourceProblem, source, s  Configure problem [Value1] with the problem config file(which will be introduced later)[Value2]\n\
  With one or more arguments:\n\
    Func, f                   Add arguments to the list of forbidden functions\n\
    Header, h                 Add arguments the list of forbidden headers\n\
	(in those arguments, \"\\,\" means \",\", \"\\(\" means \"(\")\n\
  A example:\n\
    ./judgerc：\n\
      h(fstream)\n\
      f(folk)\n\
      source(aplusb,config)\n\
      file(true)\n\
    ./config:\n\
      time(2.0)\n\
      memo(64000)\n\
      score(10)\n\
\n\
Problem config file:\n\
    Three options are supported, and the format is the same as judgerc\n\
    time, t                   Set time limit\n\
    memo, memory, m           Set memory limit\n\
    score, s                  Max score for each test point\n\
    rename, ren, r            Rename this problem\n\
\n\
CLI mode:\n"+CUIhelp+"\n\n\
SPJ:\n\
Put your spj program in the data directory of that problem, rename it as 'spj'(or you can put 'spj.cpp' in that directory, and it will be compiled automatically)\n\
SPJ arguments：\n\
    - argv[1]: Standard input file\n\
    - argv[2]: Contestant output file\n\
    - argv[3]: Standard output file\n\
    - argv[4]: Max score of this test point\n\
    - argv[5]: Score output file(must be created)with only one line, containing the score.\n\
    - argv[6]: Extra infomation(not necessary)\n\
";
		cout << help;
	}
    static void WrongArgument(char *str) {
		printf("judge: Unknown argument '%s'\nMore info with 'judge -h'\n",str);
	}
	const char InvalidHeaderFound[]="Invalid header";
	const char SourceNotFound[]="No such file or directory";
	const char InvalidWordFound[]="Invalid function";
	const char InvalidConstFound[]="Invalid word";
	const char Score[]="Score";
	const char Time[]="Time";
	const char Memory[]="Memory";
	const string Contestant="Contestant";
	const string Problem="Problem";
	const string Error="Error:";
	const string TotalScore="Score";
	const string SymbolExplanation="Key:";
	const string Rejudge="Rejudge";
	const string View="History";
	static void PressToContinue() {
		puts("Press any key to conyinue ......");
		getch();
	}
}
#endif
