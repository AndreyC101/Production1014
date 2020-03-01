#include "SDL.h" 
#include "WinMenu.h"


class WinMenu;


{

protected:

	enum state { STATE_UP, STATE_OVER, STATE_DOWN } m_state;
	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	SDL_Texture* m_pText;

	bool MouseCollision();
	virtual void Execute() = 0;

public:

	WinMenu(const char* s, SDL_Rect src, SDL_Rect dst);
	~WinMenu();
	void WinMenu::Update();
	void WinMenu::Render();





};

class checkButton(const char* s, SDL_Rect, src, SDL_Rect dst);

{

protected:

	enum state { STATE_UP, STATE_OVER, STATE_DOWN } m_state;
	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	SDL_Texture* m_pText;

	bool MouseCollision();
	virtual void Execute() = 0;

public:

	checkButton(const char* s, SDL_Rect src, SDL_Rect dst);
	~checkButton();
	void checkButton::Update();
	void checkButton::Render();

};



class checkButton : public Button

{

private:
	void Execute();

public:
	checkbutton(const char* s, SDL_Rect src, SDL_Rect dst);

};

