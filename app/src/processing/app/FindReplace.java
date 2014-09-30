/* -*- mode: java; c-basic-offset: 2; indent-tabs-mode: nil -*- */

/*
  Part of the Processing project - http://processing.org

  Copyright (c) 2004-08 Ben Fry and Casey Reas
  Copyright (c) 2001-04 Massachusetts Institute of Technology

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

package processing.app;
import static processing.app.I18n._;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

import processing.app.helpers.OSUtils;


/**
 * Find & Replace window for the Processing editor.
 * <p/>
 * One major annoyance in this is that the window is re-created each time
 * that "Find" is called. This is because Mac OS X has a strange focus
 * issue with windows that are re-shown with setVisible() or show().
 * requestFocusInWindow() properly sets the focus to the find field,
 * however, just a short moment later, the focus is set to null. Even
 * trying to catch this scenario and request it again doesn't seem to work.
 * Most likely this is some annoyance buried deep in one of Apple's docs,
 * or in the doc for the focus stuff (I tend to think the former because
 * Windows doesn't seem to be quite so beligerent). Filed as
 * <A HREF="http://dev.processing.org/bugs/show_bug.cgi?id=244"> Bug 244</A>
 * should anyone have clues about how to fix.
 */
@SuppressWarnings("serial")
public class FindReplace extends JFrame implements ActionListener {

  static final int EDGE = OSUtils.isMacOS() ? 20 : 13;
  static final int SMALL = 6;
  static final int BUTTONGAP = 12; // 12 is correct for Mac, other numbers may be required for other platofrms

  Editor editor;

  JTextField findField;
  JTextField replaceField;
  static String findString;
  static String replaceString;

  JButton replaceButton;
  JButton replaceAllButton;
  JButton replaceFindButton;
  JButton previousButton;
  JButton findButton;

  JCheckBox ignoreCaseBox;
  static boolean ignoreCase = true;

  JCheckBox wrapAroundBox;
  static boolean wrapAround = true;

  JCheckBox searchAllFilesBox;
  static boolean searchAllFiles = false;

  public FindReplace(Editor editor) {
    super("Find");
    setResizable(false);
    this.editor = editor;
    
    FlowLayout searchLayout = new FlowLayout(FlowLayout.RIGHT,5,0);
    Container pane = getContentPane();
    pane.setLayout(searchLayout);

    JLabel findLabel = new JLabel(_("Find:"));
    JLabel replaceLabel = new JLabel(_("Replace with:"));
    Dimension labelDimension = replaceLabel.getPreferredSize();
    
    JPanel find = new JPanel();
    find.add(findLabel);
    find.add(findField = new JTextField(20));
    pane.add(find);
    
    JPanel replace = new JPanel();
    replace.add(replaceLabel);
    replace.add(replaceField = new JTextField(20));
    pane.add(replace);
    
    int fieldHeight = findField.getPreferredSize().height;

    JPanel checkbox = new JPanel();
    
    // Fill the findString with selected text if no previous value
    if (editor.getSelectedText() != null &&
        editor.getSelectedText().length() > 0)
      findString = editor.getSelectedText();
    
    if (findString != null) findField.setText(findString);
    if (replaceString != null) replaceField.setText(replaceString);
    //System.out.println("setting find str to " + findString);
    //findField.requestFocusInWindow();

    ignoreCaseBox = new JCheckBox(_("Ignore Case"));
    ignoreCaseBox.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          ignoreCase = ignoreCaseBox.isSelected();
        }
      });
    ignoreCaseBox.setSelected(ignoreCase);
    checkbox.add(ignoreCaseBox);

    wrapAroundBox = new JCheckBox(_("Wrap Around"));
    wrapAroundBox.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          wrapAround = wrapAroundBox.isSelected();
        }
      });
    wrapAroundBox.setSelected(wrapAround);
    checkbox.add(wrapAroundBox);
    
    searchAllFilesBox = new JCheckBox(_("Search all Sketch Tabs"));
    searchAllFilesBox.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          searchAllFiles = searchAllFilesBox.isSelected();
        }
      });
    searchAllFilesBox.setSelected(searchAllFiles);
    checkbox.add(searchAllFilesBox);

    pane.add(checkbox);
    
    JPanel buttons = new JPanel();
    buttons.setLayout(new FlowLayout(FlowLayout.CENTER, BUTTONGAP, 0));

    // ordering is different on mac versus pc
    if (OSUtils.isMacOS()) {
      buttons.add(replaceAllButton = new JButton(_("Replace All")));
      buttons.add(replaceButton = new JButton(_("Replace")));
      buttons.add(replaceFindButton = new JButton(_("Replace & Find")));
      buttons.add(previousButton = new JButton(_("Previous")));
      buttons.add(findButton = new JButton(_("Find")));

    } else {
      buttons.add(findButton = new JButton(_("Find")));
      buttons.add(previousButton = new JButton(_("Previous"))); // is this the right position for non-Mac?
      buttons.add(replaceFindButton = new JButton(_("Replace & Find")));
      buttons.add(replaceButton = new JButton(_("Replace")));
      buttons.add(replaceAllButton = new JButton(_("Replace All")));
    }
    pane.add(buttons);

    // to fix ugliness.. normally macosx java 1.3 puts an
    // ugly white border around this object, so turn it off.
    if (OSUtils.isMacOS()) {
      buttons.setBorder(null);
    }

    /*
    findField.addFocusListener(new FocusListener() {
        public void focusGained(FocusEvent e) {
          System.out.println("Focus gained " + e.getOppositeComponent());
        }

        public void focusLost(FocusEvent e) {
          System.out.println("Focus lost "); // + e.getOppositeComponent());
          if (e.getOppositeComponent() == null) {
            requestFocusInWindow();
          }
        }
      });
    */

    Dimension buttonsDimension = buttons.getPreferredSize();
    int visibleButtonWidth = buttonsDimension.width - 2 * BUTTONGAP;
    int fieldWidth = visibleButtonWidth - (labelDimension.width + SMALL);

   // +1 since it's better to tend downwards
    int yoff = (1 + fieldHeight - labelDimension.height) / 2;

    int ypos = EDGE;
    
    int labelWidth = findLabel.getPreferredSize().width;
    findLabel.setBounds(EDGE + (labelDimension.width-labelWidth), ypos + yoff, //  + yoff was added to the wrong field
                        labelWidth, labelDimension.height);
    findField.setBounds(EDGE + labelDimension.width + SMALL, ypos,
                        fieldWidth, fieldHeight);
                        
    ypos += fieldHeight + SMALL;
    
    labelWidth = replaceLabel.getPreferredSize().width;
    replaceLabel.setBounds(EDGE + (labelDimension.width-labelWidth), ypos + yoff,
                           labelWidth, labelDimension.height);
    replaceField.setBounds(EDGE + labelDimension.width + SMALL, ypos,
                           fieldWidth, fieldHeight);

    ypos += fieldHeight + SMALL;

    ignoreCaseBox.setBounds(EDGE + labelDimension.width + SMALL,
                            ypos,
                            (fieldWidth-SMALL)/4, fieldHeight);

    wrapAroundBox.setBounds(EDGE + labelDimension.width + SMALL + (fieldWidth-SMALL)/4 + SMALL,
                            ypos,
                            (fieldWidth-SMALL)/4, fieldHeight);

	searchAllFilesBox.setBounds(EDGE + labelDimension.width + SMALL + (int)((fieldWidth-SMALL)/1.9) + SMALL,
                            ypos,
                            (fieldWidth-SMALL)/2, fieldHeight);

    ypos += fieldHeight + SMALL;

    buttons.setBounds(EDGE-BUTTONGAP, ypos,
                      buttonsDimension.width, buttonsDimension.height);

    ypos += buttonsDimension.height;

//    Dimension screen = Toolkit.getDefaultToolkit().getScreenSize();

    int wide = visibleButtonWidth + EDGE*2;
    int high = ypos; // butt.y + butt.height + EDGE*2 + SMALL;

    pack();
    Insets insets = getInsets();
    //System.out.println("Insets = " + insets);
    setSize(wide + insets.left + insets.right,high + insets.top + insets.bottom); 

    setLocationRelativeTo( null ); // center
 //   setBounds((screen.width - wide) / 2, (screen.height - high) / 2, wide, high);

    replaceButton.addActionListener(this);
    replaceAllButton.addActionListener(this);
    replaceFindButton.addActionListener(this);
    findButton.addActionListener(this);
    previousButton.addActionListener(this);

    // you mustn't replace what you haven't found, my son
    // semantics of replace are "replace the current selection with the replace field"
    // so whether we have found before or not is irrelevent
    // replaceButton.setEnabled(false);
    // replaceFindButton.setEnabled(false);

    // make the find button the blinky default
    getRootPane().setDefaultButton(findButton);

    setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
    addWindowListener(new WindowAdapter() {
        public void windowClosing(WindowEvent e) {
          handleClose();
        }
      });
    Base.registerWindowCloseKeys(getRootPane(), new ActionListener() {
        public void actionPerformed(ActionEvent actionEvent) {
          //hide();
          handleClose();
        }
      });
    Base.setIcon(this);

    // hack to to get first field to focus properly on osx
    addWindowListener(new WindowAdapter() {
        public void windowActivated(WindowEvent e) {
          //System.out.println("activating");
          /*boolean ok =*/ findField.requestFocusInWindow();
          //System.out.println("got " + ok);
          findField.selectAll();
        }
      });
  }


  public void handleClose() {
    //System.out.println("handling close now");
    findString = findField.getText();
    replaceString = replaceField.getText();

    // this object should eventually become dereferenced
    setVisible(false);
  }


  /*
  public void show() {
    findField.requestFocusInWindow();
    super.show();
    //findField.selectAll();
    //findField.requestFocus();
  }
  */


  public void actionPerformed(ActionEvent e) {
    Object source = e.getSource();

    if (source == findButton) {
      findNext();

    } else if (source == previousButton) {
      findPrevious();

    } else if (source == replaceFindButton) {
      replaceAndFindNext();

    } else if (source == replaceButton) {
      replace();

    } else if (source == replaceAllButton) {
      replaceAll();
    }
  }


  // look for the next instance of the find string to be found
  // once found, select it (and go to that line)

  private boolean find(boolean wrap,boolean backwards,boolean searchTabs,int originTab) {
    //System.out.println("Find: " + originTab);
	boolean wrapNeeded = false;
    String search = findField.getText();
    //System.out.println("finding for " + search + " " + findString);
    // this will catch "find next" being called when no search yet
    if (search.length() == 0) return false;

    String text = editor.getText();

    if (ignoreCase) {
      search = search.toLowerCase();
      text = text.toLowerCase();
    }

    int nextIndex;
    if (!backwards) {
      //int selectionStart = editor.textarea.getSelectionStart();
      int selectionEnd = editor.getSelectionStop();

      nextIndex = text.indexOf(search, selectionEnd);
      if (wrap && nextIndex == -1) {
        // if wrapping, a second chance is ok, start from beginning
        wrapNeeded = true;
      }
    } else {
      //int selectionStart = editor.textarea.getSelectionStart();
      int selectionStart = editor.getSelectionStart()-1;

      if ( selectionStart >= 0 ) {
        nextIndex = text.lastIndexOf(search, selectionStart);
      } else {
        nextIndex = -1;
      }
      if (wrap && nextIndex == -1) {
        // if wrapping, a second chance is ok, start from the end
        wrapNeeded = true;
      }
    }

    if (nextIndex == -1) {
      // Nothing found on this tab: Search other tabs if required
      if (searchTabs) {
        // editor.
        Sketch sketch = editor.getSketch();
        if (sketch.getCodeCount() > 1) {
          int realCurrentTab = sketch.getCodeIndex(sketch.getCurrentCode());

          if (originTab != realCurrentTab) {
            if (originTab < 0)
              originTab = realCurrentTab;

            if (!wrap)
              if ((!backwards && realCurrentTab + 1 >= sketch.getCodeCount()) ||
                  (backwards && realCurrentTab - 1 < 0))
                return false; // Can't continue without wrap

            if (backwards) {
              sketch.handlePrevCode();
              this.setVisible(true);
              int l = editor.getText().length() - 1;
              editor.setSelection(l, l);
            } else {
              sketch.handleNextCode();
              this.setVisible(true);
              editor.setSelection(0, 0);
            }

            return find(wrap, backwards, searchTabs, originTab);
          }
        }
      }
      
      if (wrapNeeded)
        nextIndex = backwards ? text.lastIndexOf(search) : text.indexOf(search, 0);
    }
   	
   	if (nextIndex != -1) {
      editor.setSelection(nextIndex, nextIndex + search.length());
      return true;
   	}
   
    return false;
  }


  /**
   * Replace the current selection with whatever's in the
   * replacement text field.
   */
  public void replace() {
    if (findField.getText().length() == 0)
      return;

    int newpos = editor.getSelectionStart() - findField.getText().length();
    if (newpos < 0)
      newpos = 0;
    editor.setSelection(newpos, newpos);

    boolean foundAtLeastOne = false;

    if (find(false, false, searchAllFiles, -1)) {
      foundAtLeastOne = true;
      editor.setSelectedText(replaceField.getText());
      editor.getSketch().setModified(true); // TODO is this necessary?
    }

    if (!foundAtLeastOne) {
      Toolkit.getDefaultToolkit().beep();
    }

  }

  /**
   * Replace the current selection with whatever's in the
   * replacement text field, and then find the next match
   */
  public void replaceAndFindNext() {
    replace();
    findNext();
  }

  /**
   * Replace everything that matches by doing find and replace
   * alternately until nothing more found.
   */
  public void replaceAll() {
    if (findField.getText().length() == 0)
      return;
    // move to the beginning
    editor.setSelection(0, 0);

    boolean foundAtLeastOne = false;
    while (true) {
      if (find(false, false, searchAllFiles, -1)) {
        foundAtLeastOne = true;
        editor.setSelectedText(replaceField.getText());
        editor.getSketch().setModified(true); // TODO is this necessary?
      } else {
        break;
      }
    }
    if (!foundAtLeastOne) {
      Toolkit.getDefaultToolkit().beep();
    }
  }
  
  public void setFindText( String t ) {
    findField.setText( t );
    findString = t;
  }

  public void findNext() {
    if ( !find( wrapAround, false, searchAllFiles,-1 ) ) {
      Toolkit.getDefaultToolkit().beep();
    }
  }

  public void findPrevious() {
    if ( !find( wrapAround, true, searchAllFiles,-1 ) ) {
      Toolkit.getDefaultToolkit().beep();
    }
  }

}
