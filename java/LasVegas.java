import java.util.Scanner;
import java.util.Random;

public class LasVegas {
	static Scanner sc;
	static Random randomizer = new Random();
	static Deck[] decks;
	static int money;
	static int wager;
	static int round;
	static Card[] croupier;
	static Card[] player;
	static int plIndex; // actually length
	static int crIndex; // actually length
	static boolean playing;

	public static void main(String[] args) {
		sc = new Scanner(System.in);
		decks = new Deck[6];
		round = 1;
		// money = 0;
		playing = true;
		printHeader();
		do {
			System.out.print("Balance: $");
			try {
				money = sc.nextInt();
				if (money <= 0) {
					System.out.println("Please enter a number greater than zero.");
				}
			} catch (java.util.InputMismatchException e) {
				System.out.println("Please enter a number greater than zero.");
				sc.nextLine();
			}

		} while (money <= 0);

		while (playing) {
			plIndex = 0;
			crIndex = 0;
			wager = 0;

			for (int i = 0; i < decks.length; i++) {
				decks[i] = new Deck();
				decks[i].shuffle();
			}

			player = new Card[decks.length * decks[0].getLength()];
			croupier = new Card[decks.length * decks[0].getLength()];

			if (money == 0) {
				System.out.println("You lost all your money, please come back with more.");
				break;
			} else { 
				System.out.println("\nRound " + round);
				System.out.println("-------");
				System.out.println("Balance is $" + money);
			}

			do {
				System.out.print("Wager: $");
				try {
					wager = sc.nextInt();
					if (wager > money) {
						System.out.println("You don't have that much money...");
					} else if (wager <= 0) {
						System.out.println("Minimum wager is $1 and maximum wager is $" + money + ".");
					}
				} catch (java.util.InputMismatchException e) {
					System.out.println("Please enter a non-zero natural number less than or equal to your balance.");
					sc.nextLine();
				}
				
			} while (wager > money || wager <= 0);

			money -= wager;

			hitCroupier();
			hitPlayer();
			hitPlayer();

			playGame();

			round++;
		}

		System.out.println("\nQuitting... Bye!");
		// System.out.println(deck.toString());
	}

	public static void playGame() {
		printStatus();
		int command = 0;

		do {
			System.out.print("1] Hit ... 2] Stand ... 3] Quit: ");
			try {
				command = sc.nextInt();
				if (!(command == 1 || command == 2 || command == 3)) {
					System.out.println("Please enter a number shown.");
				}
			} catch (java.util.InputMismatchException e) {
				System.out.println("That's not an integer.");
				sc.nextLine();
			}
		} while (!(command == 1 || command == 2 || command == 3));


		if (command == 1) {
			hitPlayer();
			if (getHandSum(player, plIndex) > 21) {
				printStatus();
				lose();
				return;
			} else if (getHandSum(player, plIndex) == 21) {
				System.out.println("\nYou have 21! You should stand.");
			}
			playGame();
		} else if (command == 2) {
			while (getHandSum(croupier, crIndex) < 17) {
				hitCroupier();
			}

			showHand(player, plIndex);
			printStatus();

			int crHand = getHandSum(croupier, crIndex);
			int plHand = getHandSum(player, plIndex);

			if (plHand == crHand) {
				draw();
			} else if (crHand > 21) {
				win();
			} else if (plHand > 21) {
				lose();
			} else if (21 - crHand < 21 - plHand) {
				lose();
			} else {
				win();
			}

			System.out.println();
		} else {
			playing = false;
		}
	}

	public static void lose() {
		System.out.print("\nCroupier has " + getHandSum(croupier, crIndex));
		System.out.println(" | Player has " + getHandSum(player, plIndex));
		System.out.println("House wins, you lose $" + wager + "... (┛◉Д◉)┛彡┻━┻");
	}

	public static void win() {
		money += wager * 2;
		System.out.print("\nCroupier has " + getHandSum(croupier, crIndex));
		System.out.println(" | Player has " + getHandSum(player, plIndex));
		System.out.println("Croupier loses, you win $" + wager + "! ᕕ( ᐛ )ᕗ");
	}

	public static void draw() {
		money += wager;
		System.out.print("\nCroupier has " + getHandSum(croupier, crIndex));
		System.out.println(" | Player has " + getHandSum(player, plIndex));
		System.out.println("It's a draw. 乁(ツ)ㄏ");
		System.out.println("You got your $" + wager + " back.");
	}

	public static Card getRandom() {
		return decks[randomizer.nextInt(decks.length - 1)].getRandom();
	}

	public static void hitPlayer() {
		// Card temp = getRandom();
		// temp.setVisible(false);
		// player[plIndex] = temp;

		player[plIndex] = getRandom();

		if (player[plIndex].getFace() == "A") {
			plIndex++;
			printStatus();
			System.out.print("Is this ace worth 1 or 11 points? (enter number): ");
			int points = 0;
			do {
				try {
					points = sc.nextInt();
					if (!(points == 1 || points == 11)) {
						System.out.print("Please enter either 1 or 11: ");
					} else if (points == 1) {
						System.out.println("1 it is.");
						player[plIndex - 1].switchValueAlt();
					} else if (points == 11) {
						System.out.println("11 it is.");
					}
				} catch (java.util.InputMismatchException e) {
					System.out.println("That's not an integer.");
					sc.nextLine();
					System.out.print("Please enter either 1 or 11: ");
				}
			} while (!(points == 1 || points == 11));
		} else {
			plIndex++;
		}
	}

	public static void hitCroupier() {
		croupier[crIndex] = getRandom();
		// croupier[crIndex] = new Card("A", "S");

		if (croupier[crIndex].getFace() == "A" && getHandSum(croupier, crIndex) + 11 > 21) {
			croupier[crIndex].switchValueAlt();
		}

		crIndex++;
	}

	public static int getHandSum(Card[] hand, int index) {
		int sum = 0;
		for (int i = 0; i < index; i++) {
			sum += hand[i].getValue();
		}
		return sum;
	}

	public static void showHand(Card[] hand, int index) {
		for (int i = 1; i < index; i++) {
			hand[i].setVisible(true);
		}
	}

	public static String getPlayer() {
		String temp = "";
		for (int i = 1; i < plIndex; i++) {
			temp += " | " + player[i].toString();
		}
		return temp;
	}

	public static String getCroupier() {
		String temp = "";
		for (int i = 1; i < crIndex; i++) {
			temp += " | " + croupier[i].toString();
		}
		return temp;
	}

	public static void printStatus() {
		System.out.println("\nCroupier: " + croupier[0].toString() + getCroupier());
		System.out.println("Player: " + player[0].toString() + getPlayer());
	}

	public static void printHeader() {
		String title = "Java Casino v0.4.1";
		String game = "Blackjack";
		String copyright = "© Miles Prinzen 2017";
		System.out.println(String.format("|%27s|", "").replaceAll(" ", "="));
		String format = "|%1$22s     |\n|%2$18s         |\n|   %3$20s    |\n";
		System.out.format(format, title, game, copyright);
		System.out.println(String.format("|%27s|", "").replaceAll(" ", "="));
	}
}