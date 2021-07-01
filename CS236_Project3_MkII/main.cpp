#include "Parser.h"
#include "DatabaseManager.h"
#include "Lexer.h"
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
	string file = argv[0];
	Lexer testLexer;
	Parser testParser;
	Database baseOfData;
	DatabaseManager dbManager;
	//vector<Predicate> queries = testParser.getQueries();
	testLexer.scan(file);
	testParser.parse(testLexer.getVector());
	dbManager.manage(baseOfData, testParser.getQueries(), testParser.getDomain());
	return 0;
}