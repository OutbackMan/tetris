from aqt import mw

from aqt.utils import showInfo

from aqt.qt import *

def addon_functionality():
    deck_id = mw.col.decks.id("Encoding")
    deck = mw.col.decks.get(deck_id)
    # look at REPL
    
    cardCount = mw.col.cardCount()
    # show a message box
    showInfo("Card count: %d" % cardCount)


run_addon = QAction("addon", mw)
run_addon.triggered.connect(addon_functionality)

mw.form.menuTools.addAction(run_addon)
