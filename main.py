#with open('input.txt') as f:
#    decks = [list(map(int, d.strip().split('\n')[1:])) for d in f.read().split('\n\n')]

decks = [
    [28,50,9,11,4,45,19,26,42,43,31,46,21,40,33,20,7,6,17,44,5,39,35,27,10],
    [18,16,29,41,14,12,30,37,36,24,48,38,47,34,15,8,49,23,1,3,32,25,22,13,2]]

def deckid(deck):
    id = weight = 0
    for card in deck[::-1]:
        weight += 1
        id += weight * card
    return id

def gameid(decks):
    return [deckid(d) for d in decks]

# Part 1
#def combat1(decks):
#    while len(decks[0]) and len(decks[1]):
#        draw = [d.pop(0) for d in decks]
#        w = 0 if draw[0] > draw[1] else 1
#        decks[w].extend([draw[w], draw[1 - w]])
#    return sum(gameid(decks))

#print(combat1(deepcopy(decks)))

# Part 2
def combat2(decks):
    state = set()
    while len(decks[0]) and len(decks[1]):
        i, j = gameid(decks)
        id = 10000 * i + j  # unique enough
        if id in state:
            return 0  # player 1 wins
        else:
            state.add(id)
        draw = [d.pop(0) for d in decks]
        if len(decks[0]) >= draw[0] and len(decks[1]) >= draw[1]:
            w = combat2([decks[0][:draw[0]], decks[1][:draw[1]]])
        else:
            w = 0 if draw[0] > draw[1] else 1
        decks[w].extend([draw[w], draw[1 - w]])
    return 0 if len(decks[0]) else 1

print(deckid(decks[combat2(decks)]))
