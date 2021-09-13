#include <iostream>
#include <ctime>
using namespace std;
int main()
{
    //Tillåter specialkaraktärer som å,ä och ö
    locale::global(std::locale{ ".utf-8" });
    int pengarSatsade = 0, tempPengarSatsade = 0, konto = 0, spelareSumma = 0, datorSumma = 0, 
        slumptal, spelareTarningskast, datorTarningskast, Insattning = 0, pcPoints = 0, playerPoints = 0;
    bool ongoingGame = true, valid=false, valid2=false;
    char svar, svar2;
    srand(time(0));

    //teeeeeeeeeeeeeeeeest
    while (ongoingGame=true)
    {// kommentar
        bool ongoingRound = true;
        spelareSumma = 0, datorSumma = 0;
        cout << "Välkommen till tärningsspelet!\nDitt nuvarande saldo är: " << konto << ". Vill du sätta in mer? Max 5000kr åt gången. 'Y|N'" << endl;
        
        while (!valid2) 
        {
            cin >> svar;
            if (svar == 'N' && konto < 100)
            {
                valid2 = true;
                while (svar == 'N')
                {
                    cout << "Ditt saldo är för lågt och för att spela krävs pengar. Vill du sätta in mer? Max 5000kr åt gången. 'Y|N'" << endl;
                    cin >> svar;
                }
            }

            if (svar == 'Y')
            {
                valid2 = true;
                cout << "Ange antal kronor. Max 5000: " << endl;
                cin >> Insattning;
                while (Insattning > 5000 || Insattning < 100)
                {
                    if (Insattning > 5000)
                    {
                        cout << "För stor insättning, försök igen! Max 5000kr." << endl;
                        cin >> Insattning;
                    }
                    else if (Insattning < 100)
                    {
                        cout << "För liten insättning. Minst 100 krävs för att spela. Försök igen: " << endl;
                        cin >> Insattning;
                    }
                }
                konto += Insattning;
                cout << "Insättning klar. Saldo: " << konto << endl;
            }
        }
        while (!valid) 
        {
            cout << "Vänligen ange hur mycket pengar du vill satsa för egen vinst.\n'1' för 100kr\n'3' för 300kr\n'5' för 500kr " << endl;
            cin >> tempPengarSatsade;
        
            if (tempPengarSatsade == 1 && konto > 99)
            {
                pengarSatsade = 100;
                valid = true;
            }
            else if (tempPengarSatsade == 3 && konto >= 300)
            {
                pengarSatsade = 300;
                valid = true;
            }
            else if (tempPengarSatsade == 5 && konto >= 500)
            {
                pengarSatsade = 500;
                valid = true;
            }
            else
            {
                cout << "Felaktig inmatning" << endl;
            }
        }

        cout << "Nu börjar spelet!"<<endl;
        while (ongoingRound)
        {
            if (spelareSumma == 2)
            {
                cout << "Spelaren vann!" << endl;
                konto += pengarSatsade;
                playerPoints++;
                cout << "Nu har spelaren vunnit " << konto << "kr.\n Ditt saldo är nu: " << konto<< "kr" << endl;
                cout << "Totala poäng\n Spelare: " << playerPoints << "\nDator: " << pcPoints<<endl;
                ongoingRound = false;
                break;
            }
            else if (datorSumma == 2)
            {
                cout << "Vad synd ): datorn vann." << endl;
                konto -= pengarSatsade;
                pcPoints++;
                cout << "Nu har spelaren förlorat " << pengarSatsade << " kr.\nDitt saldo är nu: "<<  konto << "kr"  << endl;
                cout << "Totala poäng=\nSpelare: " << playerPoints << "\nDator: " << pcPoints<<endl;
                ongoingRound = false;
                break;
            }
            spelareTarningskast = rand() % 6 + 1;
            cout << "Spelaren slog en: " << spelareTarningskast <<endl;
            datorTarningskast = rand() % 6 + 1;
            cout << "Datorn slog en: " << datorTarningskast << "\n\n";

            if (spelareTarningskast == datorTarningskast) 
            {
                cout << "Det blev lika.\n---------------\n";
            }
            else if (spelareTarningskast > datorTarningskast) 
            {
                spelareSumma++;
                cout << "Nu har spelaren " << spelareSumma << "poäng\n---------------\n";
            }
            else if ( datorTarningskast> spelareTarningskast) 
            {
                datorSumma++;
                cout << "Nu har datorn " << datorSumma << " poäng\n---------------\n";
            }
        }

        cout << "Vill du spela igen?: 'Y|N'" << endl;
        cin >> svar2;
        valid = false;
        valid2 = false;

        if (svar2=='N')
        {
            ongoingGame = false;
            break;
        }
    }
    cout << "Spelet avslutas";
    cin.ignore();
    
}


