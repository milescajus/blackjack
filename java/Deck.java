import java.util.Random;

public class Deck {
	private Random randomizer = new Random();
	private String[] faces = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
	private String[] suits = {"S", "D", "H", "C"};
	private Card[] deck = new Card[52];

	Deck() {
		for (int i = 0; i < deck.length; i++) {
			deck[i] = new Card(faces[i % 13], suits[i / 13]);
		}
	}

	public void shuffle() {
		for (int i = 0; i < deck.length; i++) {
			int positionRandom = randomizer.nextInt(deck.length - 1);
			Card temp = deck[i];
			deck[i] = deck[positionRandom];
			deck[positionRandom] = temp;
		}
	}

	public Card getRandom() {
		Card temp = deck[randomizer.nextInt(deck.length - 1)].take();
		if (temp == null) {
			temp = getRandom();
		}
		return temp;
	}

	public int getLength() {
		return deck.length;
	}

	public String toString() {
		String deckString = "";
		for (Card c : deck) {
			deckString += c.toString() + "\n";
		}

		return deckString;
	}
}