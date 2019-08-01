from aqt import mw

from aqt.utils import showInfo

from aqt.qt import *

def addon_functionality():
    deck_id = mw.col.decks.id("Encodings")
    deck = mw.col.decks.get(deck_id)
    
    # create a media directory
    deck.media.dir()
    
    # put a file into it
    file = str(os.path.join(testDir, "support/fake.png"))
    d.media.addFile(file)
    # add a note which references it
    f = d.newNote()
    f['Front'] = "one"; f['Back'] = "<img src='fake.png'>"
    d.addNote(f)
    
    card = deck.newNote()
    card['Front'] = image
    card['Back'] = image_title
    
    deck.addNote(card)
    
    cardCount = mw.col.cardCount()
    # show a message box
    showInfo("Card count: %d" % cardCount)


run_addon = QAction("addon", mw)
run_addon.triggered.connect(addon_functionality)

mw.form.menuTools.addAction(run_addon)

# http://theremin.music.uiowa.edu/MISpiano.html
# https://stackoverflow.com/questions/45540860/download-all-the-files-in-the-website
