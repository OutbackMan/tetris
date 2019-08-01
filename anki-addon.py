# tools --> add-ons folder --> name/__init__.py

from aqt import mw

from aqt.utils import showInfo

from aqt.qt import *

import os

# This will add to default deck
def populate_encoding_deck():
    deck_id = mw.col.decks.id("Encodings")
    deck = mw.col.decks.get(deck_id)
    
    # INFO(Ryan): Create a media directory.
    mw.col.media.dir()
    
    images_dir = os.path.join(os.path.dirname(__file__), "images")
    for file_name in os.listdir(images_dir):
        media_file_path = os.path.join(images_dir, file_name)
        mw.col.media.addFile(media_file_path)

        new_note = mw.col.newNote()
        new_note["Front"] = "<img src='{0}'>".format(file_name)
        new_note["Back"] = os.path.splitext(file_name)[0]
        mw.col.addNote(new_note)

'''
    file = str(os.path.join(os.path.dirname(__file__), "support/fake.png"))
    d.media.addFile(file)
    # add a note which references it
    f = d.newNote()
    f['Front'] = "one"; f['Back'] = "<img src='fake.png'>"
    # <audio src='file.mp3'>
    d.addNote(f)
    
    card = deck.newNote()
    card['Front'] = image
    card['Back'] = image_title
    
    deck.addNote(card)
    
    cardCount = mw.col.cardCount()
    # show a message box
    showInfo("Card count: %d" % cardCount)
'''


populate_encoding_deck_menu_item = QAction("populate_encoding_deck", mw)
populate_encoding_deck_menu_item.triggered.connect(populate_encoding_deck)
mw.form.menuTools.addAction(populate_encoding_deck_menu_item)
