#include "MyMenu.h"

bool MyMenu::onTouchBegan(Touch* touch, Event* event)
{
    
    moved = false;
    return CCMenu::onTouchBegan(touch, event);
    
}
void MyMenu::onTouchEnded(Touch* touch, Event* event)
{
    if(!moved)
    {
        CCMenu::onTouchEnded(touch, event);
    }
    
    if (_selectedItem)
    {
        _selectedItem->unselected();
    }

    _state = Menu::State::WAITING;
   
}
void MyMenu::onTouchMoved(Touch* touch, Event* event)
{
    moved = true;
    CCMenu::onTouchMoved(touch, event);
}