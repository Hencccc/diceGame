#include <iostream>
#include <ctime>
using namespace std;
int main()
{
	//Tillåter specialkaraktärer som å,ä och ö
	setlocale(LC_ALL, ".UTF8");
	//Initiering och deklaration av programmets variabler
	int dice1=0, dice2=0, dice3=0, dice4=0, pengarSatsade = 0, tempPengarSatsade = 0, konto = 0, spelareSumma = 0, datorSumma = 0,
		spelareHighestDice=0, datorHighestDice=0, Insattning = 0, pcPoints = 0, playerPoints = 0;
	bool ongoingGame = true, betPlaced = false, insattningValid = false, ongoingRound = true;
	char svar, svar2;
	srand(time(0));

	//Gameloop, körs om och om igen tills användaren matar in 'N' i slutet av programmet
	while (ongoingGame) {
		/*Kontrollerar att användaren har tillräckligt med pengar på kontot och hanterar annars en insättning.
		 Skriver ut instruktioner och tar emot input.*/
		while (!insattningValid) {
			cout << "Välkommen till tärningsspelet!\nDitt nuvarande saldo är: " << konto << ". Vill du sätta in mer? Max 5000kr åt gången. 'Y|N'" << endl;
			cin >> svar;
			/*Om användaren svarar 'N' och användarens konto är under 100kr krävs denna att svara 'Y' för att kunna spela.
			Vid input ges "svar" ett nytt värde och whileloopen körs till man svarat 'Y'.
			Annars körs loopen om och om igen tills programmet avslutas.*/
			if (svar == 'N' && konto < 100) {
				while (svar != 'Y') {
					cout << "Ditt saldo är för lågt och för att spela krävs pengar. Vill du sätta in mer? Max 5000kr åt gången. 'Y|N'" << endl;
					cin >> svar;
				}
			}
			//När användaren svarat 'Y' sköts insättningen. Output ger instruktioner, input lagras i "Insattning"
			if (svar == 'Y') {
				cout << "Ange antal kronor. Max 5000: " << endl;
				cin >> Insattning;
				/*Är insättningen utanför gränserna körs whileloopen där man på nytt får ge ny input till Insattning tills 
				insättningen är giltig. Beroende på vilken gräns insättningsförsöket över/underskridit ges olika output.*/
				while (Insattning > 5000 || Insattning < 100) {
					if (Insattning > 5000) {
						cout << "För stor insättning, försök igen! Max 5000kr." << endl;
						cin >> Insattning;
					}
					else if (Insattning < 100) {
						cout << "För liten insättning. Minst 100 krävs för att spela. Försök igen: " << endl;
						cin >> Insattning;
					}
				}
				/*Vid giltigt belopp ökas kontots värde med aktuell insättning, "insattningValid" sätts till true
				vilket gör att man tillslut kommer vidare i spelet. Sedan ges output med aktuellt saldo.*/
				konto += Insattning;
				insattningValid = true;
				cout << "Insättning klar. Saldo: " << konto << endl;
			}
			//Har man tillräckligt med pengar och svarar nej får man gå vidare, "insattningValid" sätts till true och man kommer vidare i spelet.
			else if(svar == 'N') {
				insattningValid = true;
			}
			//Har man matat in fel input får man försöka igen och stora whileloopen körs om.
			else {
				cout << "Försök igen!\n";
			}
		}
		//Loop som kontrollerar satsning för aktuell omgång. Output med instruktioner ges och input tas emot.
		while (!betPlaced) {
			cout << "Vänligen ange hur mycket pengar du vill satsa för egen vinst.\n'1' för 100kr\n'3' för 300kr\n'5' för 500kr " << endl;
			cin >> tempPengarSatsade;
			/*Beroende på svarsalternativ kontrolleras det att kontot har tillräckligt med pengar för aktuellt bet.
			Har man bara 100kr på kontot ska man inte kunna betta t.ex. 300kr.
			Vid felaktig inmatning eller vid felaktigt försök att betta mer pengar skrivs detta ut och whileloopen körs om.
			Vid korrekt inmatning placeras betets värde i "pengarSatsade" och whileloopen sätts till sann och programmet körs vidare.*/
			if (tempPengarSatsade == 1 && konto >= 100) {
				pengarSatsade = 100;
				betPlaced = true;
			}
			else if (tempPengarSatsade == 3 && konto >= 300) {
				pengarSatsade = 300;
				betPlaced = true;
			}
			else if (tempPengarSatsade == 5 && konto >= 500) {
				pengarSatsade = 500;
				betPlaced = true;
			}
			else {
				cout << "Felaktig inmatning" << endl;
			}
		}
		//Output ges att spelet börjar och här har vi en loop för en spelomgång
		cout << "Nu börjar spelet!" << endl;
		while (ongoingRound) {
			/*I början kontrolleras det ifall antingen spelaren eller datorn har vunnit, dvs kommit upp i 2 poäng.
			Då ges en output som meddelar att spelaren vann, pengarna som spelaren satsat adderas till kontot och spelarens totala poäng ökar med 1.
			Då skrivs det ut hur mycket pengar spelaren vunnit, aktuellt saldo och spelets totala poäng. 
			"ongoingRound" ändras till */
			if (spelareSumma == 2) {
				cout << "Spelaren vann!" << endl;
				konto += pengarSatsade;
				playerPoints++;
				cout << "Nu har spelaren vunnit " << pengarSatsade << "kr.\n Ditt saldo är nu: " << konto << "kr" << endl;
				cout << "Totala poäng\n Spelare: " << playerPoints << "\nDator: " << pcPoints << endl;
				ongoingRound = false;
				break;
			}
			/*Annars kontrolleras det ifall antingen datorn har vunnit, dvs kommit upp i 2 poäng.
			Då ges en output som meddelar att datorn vann, pengarna som spelaren satsat subtraheras från kontot och datorns totala poäng ökar med 1.
			Då skrivs det ut hur mycket pengar spelaren förlorat, aktuellt saldo och spelets totala poäng.
			"ongoingRound" ändras till false och vi breakar ut ifrån whileloopen. */
			else if (datorSumma == 2) {
				cout << "Vad synd ): datorn vann." << endl;
				konto -= pengarSatsade;
				pcPoints++;
				cout << "Nu har spelaren förlorat " << pengarSatsade << " kr.\nDitt saldo är nu: " << konto << "kr" << endl;
				cout << "Totala poäng=\nSpelare: " << playerPoints << "\nDator: " << pcPoints << endl;
				ongoingRound = false;
				break;
			}
			//Spelarens kast: 2 kast slås men det största sparas samt tärningarnas resultat skrivs ut. 
			dice1 = rand() % 6 + 1;
			cout << "Spelaren första slag blev: " << dice1 << endl;
			dice2 = rand() % 6 + 1;
			cout << "Spelaren andra slag blev: " << dice2 << endl;
			//Här kontrolleras vilken tärning som är störst, där denna sparas. Output ges med resultatet. Om kasten är lika sparas bara den ena av dessa.
			if (dice1 > dice2) {
				cout << "Spelarens högsta tärning är: " << dice1 << "\n\n";
				spelareHighestDice = dice1;
			}
			else if (dice2 > dice1) {
				cout << "Spelarens högsta tärning är: " << dice2 << "\n\n";
				spelareHighestDice = dice2;
			}
			else if (dice2 == dice1) {
				cout << "Spelarens båda tärningar blev: " << dice1 << "\n\n";
				spelareHighestDice = dice1;
			}
			//Datorns kast: 2 kast slås men det största sparas. 
			dice3 = rand() % 6 + 1;
			cout << "Datorns första slag blev: " << dice3 << endl;
			dice4 = rand() % 6 + 1;
			cout << "Datorns andra slag blev: " << dice4 << endl;
			//Här kontrolleras vilken tärning som är störst, där denna sparas. Output ges med resultatet. Om kasten är lika sparas bara den ena av dessa.
			if (dice3 > dice4) {
				cout << "Datorns högsta tärning är: " << dice3 << "\n\n";
				datorHighestDice = dice3;
			}
			else if (dice3 < dice4) {
				cout << "Datorns högsta tärning är: " << dice4 << "\n\n";
				datorHighestDice = dice4;
			}
			else if (dice3 == dice4) {
				cout << "Datorns båda tärningar blev: " << dice3 << "\n\n";
				datorHighestDice = dice3;
			}
			/*Här jämförs datorns och spelarens högsta tärningar mot varandra. Den som har högst tärning får ett poäng i aktuell omgång.
			Blir resultaten lika skrivs detta ut och inget resultat sparas.*/
			if (spelareHighestDice == datorHighestDice) {
				cout << "Det blev lika.\n---------------\n";
			}
			else if (spelareHighestDice > datorHighestDice) {
				spelareSumma++;
				cout << "Nu har spelaren " << spelareSumma << " poäng\n---------------\n";
			}
			else if (datorHighestDice > spelareHighestDice) {
				datorSumma++;
				cout << "Nu har datorn " << datorSumma << " poäng\n---------------\n";
			}
		}
		/*Efter spelad omgång ges möjligheten att spela igen. Omgångspoängen och booleaner som kontrollerar loopar nollställs.
		Svarar man 'N' sätts gameloopen till false och vi går förbi den loopen */
		cout << "Vill du spela igen?: 'Y|N'" << endl;
		cin >> svar2;
		spelareSumma = 0, datorSumma = 0;
		betPlaced = false;
		ongoingRound = true;
		insattningValid = false;

		if (svar2 == 'N') {
			ongoingGame = false;
		}
	}
	//Spelet avslutas
	cout << "Spelet avslutas";
	cin.ignore();
	return 0;
}


