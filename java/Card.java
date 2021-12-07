public class Card {
	private int value;
	private int value_alt;
	private String face;
	private String suit;
	private boolean isVisible;
	private boolean inDeck;

	Card(String face, String suit) {
		this.face = face;
		this.suit = suit;
		value_alt = 0;
		findValue(face);
		isVisible = true;
		inDeck = true;
	}

	private void findValue(String face) {
		switch (face) {
			case "2": this.value = 2; break;
			case "3": this.value = 3; break;
			case "4": this.value = 4; break;
			case "5": this.value = 5; break;
			case "6": this.value = 6; break;
			case "7": this.value = 7; break;
			case "8": this.value = 8; break;
			case "9": this.value = 9; break;
			case "10": this.value = 10; break;
			case "J": this.value = 10; break;
			case "Q": this.value = 10; break;
			case "K": this.value = 10; break;
			case "A": this.value = 11; this.value_alt = 1; break; // ace can be (1) or (11)
		}
	}

	public int getValue() {
		return value;
	}

	public String getFace() {
		return face;
	}

	public void switchValueAlt() {
		if (value_alt != 0) {
			value = value_alt;
		}
	}

	public Card take() {
		if (inDeck) {
			return this;		
		} else return null;
	}

	public void setVisible(boolean bool) {
		isVisible = bool;
	}

	public String toString() {
		if (isVisible) {
			return new String(face + ":" + suit + " (" + value + ")");
		} else {
			return new String("#:#");
		}
	}

}