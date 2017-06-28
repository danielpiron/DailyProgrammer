class Game():

    def __init__(self):
        self._cards = [[], []]
        self._cards_on_table = [[], []]

    def deal(self, player, cardvalue):
        self._cards[player].append(cardvalue)

    def draw_cards(self, maxcards=1):

        if not self._cards[0] and not self._cards[1]:
            return 0

        for _ in range(maxcards):
            self._cards_on_table[0].append(self._cards[0].pop(0))
            self._cards_on_table[1].append(self._cards[1].pop(0))

        player1 = self._cards_on_table[0][-1]
        player2 = self._cards_on_table[1][-1]

        if player1 > player2:
            return 1
        elif player2 > player1:
            return 2
        else:
            return self.draw_cards(3)
