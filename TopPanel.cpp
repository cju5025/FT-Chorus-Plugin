#include "TopPanel.h"
#include "InterfaceDefines.h"

FTChorusTopPanel::FTChorusTopPanel(FTChorusAudioProcessor* inProcessor)
:   FTChorusPanelBase(inProcessor)
{
    setSize(TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT);
}

FTChorusTopPanel::~FTChorusTopPanel()
{
    
}

void FTChorusTopPanel::paint(Graphics& g)
{
    const Font font_1 ( "Helvetica Neue", 22.00f, Font::bold);
    
    FTChorusPanelBase::paint(g);
    
    g.setColour(Colour(1, 124, 168));
    g.setFont( font_1 );
    g.drawFittedText("FT Chorus", 0, 0, getWidth() - 10, getHeight(), Justification::centred, 1);
}
