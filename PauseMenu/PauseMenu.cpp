#include "SDL.h" 
#include "StartMenu.h"


class PauseMenu;


{

protected:

	enum state { STATE_UP, STATE_OVER, STATE_DOWN } m_state;
	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	SDL_Texture* m_pText;

	bool MouseCollision();
	virtual void Execute() = 0;

public:

	PauseMenu(const char* s, SDL_Rect src, SDL_Rect dst);
	~PauseMenu();
	void PauseMenu::Update();
	void PauseMenu::Render();





};

class Button(const char* s, SDL_Rect, src, SDL_Rect dst);

{

protected:

	enum state { STATE_UP, STATE_OVER, STATE_DOWN } m_state;
	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	SDL_Texture* m_pText;

	bool MouseCollision();
	virtual void Execute() = 0;

public:

	Button(const char* s, SDL_Rect src, SDL_Rect dst);
	~Button();
	void Update();
	void Render();

};



class PlayButton : public Button

{

private:
	void Execute();

public:
	Playbutton(const char* s, SDL_Rect src, SDL_Rect dst);

};

class Exitbutton : public button
{
private:
	void Execute();
public:
	ExitButton(consta char* s, SDL_Rectsrc, SDL_Rect dst);

	class ResumeButton : public Button
	{

	private:
		void Execute();
	public:
		RestartButton(const char* s, SDL_Rect src, SDL_Rect dst);

	};