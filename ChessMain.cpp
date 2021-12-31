#include "ChessBoard.h"

#include <iostream>

using std::cout;

int main()
{
	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";

	ChessBoard cb;
	cout << '\n';

	cb.submitMove("D7", "D6");
	cout << '\n';

	cb.submitMove("D4", "H6");
	cout << '\n';

	cb.submitMove("BB", "A1");
	cout << '\n';

	cb.submitMove("B10", "A1");
	cout << '\n';

	cb.submitMove("B0", "A1");
	cout << '\n';

	cb.submitMove("D2", "D4");
	cout << '\n';

	cb.submitMove("F8", "B4");
	cout << '\n';

	cout << "=========================\n";
	cout << "Alekhine vs. Vasic (1931)\n";
	cout << "=========================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("E2", "E4");
	cb.submitMove("E7", "E6");
	cout << '\n';

	cb.submitMove("D2", "D4");
	cb.submitMove("D7", "D5");
	cout << '\n';

	cb.submitMove("B1", "C3");
	cb.submitMove("F8", "B4");
	cout << '\n';

	cb.submitMove("F1", "D3");
	cb.submitMove("B4", "C3");
	cout << '\n';

	cb.submitMove("B2", "C3");
	cb.submitMove("H7", "H6");
	cout << '\n';

	cb.submitMove("C1", "A3");
	cb.submitMove("B8", "D7");
	cout << '\n';

	cb.submitMove("D1", "E2");
	cb.submitMove("D5", "E4");
	cout << '\n';

	cb.submitMove("D3", "E4");
	cb.submitMove("G8", "F6");
	cout << '\n';

	cb.submitMove("E4", "D3");
	cb.submitMove("B7", "B6");
	cout << '\n';

	cb.submitMove("E2", "E6");
	cb.submitMove("F7", "E6");
	cout << '\n';

	cb.submitMove("D3", "G6");
	cout << '\n';

	cout << "=========================\n";
	cout << "RETI vs.TARAKOWER \n";
	cout << "=========================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("E2", "E4");
	cb.submitMove("C7", "C6");
	cout << '\n';

	cb.submitMove("D2", "D4");
	cb.submitMove("D7", "D5");
	cout << '\n';

	cb.submitMove("B1", "C3");
	cb.submitMove("D5", "E4");
	cout << '\n';

	cb.submitMove("C3", "E4");
	cb.submitMove("G8", "F6");
	cout << '\n';

	cb.submitMove("D1", "D3");
	cb.submitMove("E7", "E5");
	cout << '\n';

	cb.submitMove("D4", "E5");
	cb.submitMove("D8", "A5");
	cout << '\n';

	cb.submitMove("C1", "D2");
	cb.submitMove("A5", "E5");
	cout << '\n';

	cb.submitMove("E1", "C1");
	cb.submitMove("F6", "E4");
	cout << '\n';

	cb.submitMove("D3", "D8");
	cb.submitMove("E8", "D8");
	cout << '\n';

	cb.submitMove("D2", "G5");
	cb.submitMove("D8", "C7");
	cout << '\n';

	cb.submitMove("G5", "D8");
	cout << '\n';

	cout << "=========================\n";
	cout << "KRAMNIK vs.BELIAVSKY \n";
	cout << "=========================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("G1", "F3");
	cb.submitMove("D7", "D5");
	cout << '\n';

	cb.submitMove("G2", "G3");
	cb.submitMove("C7", "C6");
	cout << '\n';

	cb.submitMove("F1", "G2");
	cb.submitMove("C8", "G4");
	cout << '\n';

	cb.submitMove("E1", "G1");
	cb.submitMove("B8", "D7");
	cout << '\n';

	cb.submitMove("D2", "D4");
	cb.submitMove("E7", "E6");
	cout << '\n';

	cb.submitMove("B1", "D2");
	cb.submitMove("F7", "F5");
	cout << '\n';

	cb.submitMove("C2", "C4");
	cb.submitMove("F8", "D6");
	cout << '\n';

	cb.submitMove("D1", "B3");
	cb.submitMove("A8", "B8");
	cout << '\n';

	cb.submitMove("F1", "E1");
	cb.submitMove("G8", "H6");
	cout << '\n';

	cb.submitMove("C4", "D5");
	cb.submitMove("C6", "D5");
	cout << '\n';

	cb.submitMove("H2", "H3");
	cb.submitMove("G4", "H5");
	cout << '\n';

	cb.submitMove("E2", "E4");
	cb.submitMove("F5", "E4");
	cout << '\n';

	cb.submitMove("F3", "G5");
	cb.submitMove("H5", "F7");
	cout << '\n';

	cb.submitMove("D2", "E4");
	cb.submitMove("D5", "E4");
	cout << '\n';

	cb.submitMove("G5", "E6");
	cb.submitMove("F7", "E6");
	cout << '\n';

	cb.submitMove("B3", "E6");
	cb.submitMove("D8", "E7");
	cout << '\n';

	cb.submitMove("E1", "E4");
	cb.submitMove("E8", "D8");
	cout << '\n';

	cb.submitMove("E6", "D5");
	cout << '\n';

	cout << "=========================\n";
	cout << "Alekhine vs.Nenarokov \n";
	cout << "=========================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("D2", "D4");
	cb.submitMove("D7", "D5");
	cout << '\n';

	cb.submitMove("C2", "C4");
	cb.submitMove("B8", "C6");
	cout << '\n';

	cb.submitMove("G1", "F3");
	cb.submitMove("C8", "G4");
	cout << '\n';

	cb.submitMove("C4", "D5");
	cb.submitMove("D8", "D5");
	cout << '\n';

	cb.submitMove("B1", "C3");
	cb.submitMove("D5", "A5");
	cout << '\n';

	cb.submitMove("D4", "D5");
	cb.submitMove("E8", "C8");
	cout << '\n';

	cb.submitMove("C1", "D2");
	cb.submitMove("G4", "F3");
	cout << '\n';

	cb.submitMove("E2", "F3");
	cb.submitMove("C6", "B4");
	cout << '\n';

	cb.submitMove("A2", "A3");
	cb.submitMove("B4", "D5");
	cout << '\n';

	cb.submitMove("C3", "A4");
	cout << '\n';

	cout << "=========================\n";
	cout << "Short Mate \n";
	cout << "=========================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("H2", "H4");
	cb.submitMove("E7", "E5");
	cout << '\n';

	cb.submitMove("G2", "G4");
	cb.submitMove("B8", "C6");
	cout << '\n';

	cb.submitMove("F2", "F4");
	cb.submitMove("E5", "F4");
	cout << '\n';

	cb.submitMove("E2", "E4");
	cb.submitMove("D7", "D5");
	cout << '\n';

	cb.submitMove("E4", "D5");
	cb.submitMove("D8", "D5");
	cout << '\n';

	cb.submitMove("B1", "C3");
	cb.submitMove("D5", "H1");
	cout << '\n';

	cb.submitMove("G1", "E2");
	cb.submitMove("H1", "H4");
	cout << '\n';

	cb.submitMove("E2", "G3");
	cb.submitMove("H4", "G3");
	cout << '\n';

	cb.submitMove("E1", "E2");
	cb.submitMove("C8", "G4");
	cout << '\n';

	cout << "=========================\n";
	cout << "Special Moves \n";
	cout << "=========================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("G1", "F3");
	std::cout << '\n';

	cb.submitMove("H7", "H5");
	std::cout << '\n';

	cb.submitMove("G2", "G4");
	std::cout << '\n';

	cb.submitMove("H8", "H6");
	std::cout << '\n';

	cb.submitMove("F1", "G2");
	std::cout << '\n';

	cb.submitMove("A7", "A5");
	std::cout << '\n';

	cb.submitMove("E1", "G1");
	std::cout << '\n';

	cb.submitMove("A5", "A4");
	std::cout << "\n";

	cb.submitMove("G1", "H1");
	std::cout << '\n';

	cb.submitMove("H5", "G4");
	std::cout << '\n';

	cb.submitMove("H2", "H4");
	std::cout << '\n';

	cb.submitMove("A4", "A3");
	std::cout << '\n';

	cb.submitMove("H4", "H5");
	std::cout << '\n';

	cb.submitMove("A3", "B2");
	std::cout << '\n';

	cb.submitMove("C2", "C3");
	std::cout << '\n';

	cb.submitMove("B2", "A1");
	std::cout << '\n';

	return 0;
}
