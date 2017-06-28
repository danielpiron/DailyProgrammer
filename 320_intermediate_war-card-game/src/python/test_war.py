import unittest
import war


class TestWarCardGame(unittest.TestCase):

    def test_draw_cards_empty(self):
        game = war.Game()
        self.assertEqual(0, game.draw_cards())

    def test_draw_one_card_player1_wins(self):
        game = war.Game()
        game.deal(0, 2)
        game.deal(1, 1)
        self.assertEqual(1, game.draw_cards())

    def test_draw_one_card_player2_wins(self):
        game = war.Game()
        game.deal(0, 1)
        game.deal(1, 2)
        self.assertEqual(2, game.draw_cards())

    def test_draw_twice(self):
        game = war.Game()
        game.deal(0, 2)
        game.deal(0, 1)
        game.deal(1, 1)
        game.deal(1, 2)
        self.assertEqual(1, game.draw_cards())
        self.assertEqual(2, game.draw_cards())

    def test_cause_subwar_player1_wins(self):
        game = war.Game()
        game.deal(0, 1)
        game.deal(0, 1)
        game.deal(0, 1)
        game.deal(0, 2)
        game.deal(1, 1)
        game.deal(1, 2)
        game.deal(1, 2)
        game.deal(1, 1)
        self.assertEqual(1, game.draw_cards())



if __name__ == '__main__':
    unittest.main()
