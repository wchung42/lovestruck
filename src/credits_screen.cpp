#include "credits_screen.hpp"

CreditsScreen::CreditsScreen(
	raylib::Font& font,
	raylib::Texture2DUnmanaged backButtonTexture)
	: m_font(font), m_backButtonTexture(backButtonTexture)
{

}

CreditsScreen::~CreditsScreen() {};

void CreditsScreen::InitScreen()
{
	// Initialize headings and text
	float headingTextYOffset {15.0f};
	float sectionYOffset {25.0f};

	// Designer, Developer, Texture heading and text
	m_designerHeading = raylib::Text(
		m_font,
		std::string("Designer, Developer, Textures"),
		55.0f,
		1.0f,
		BLACK
	);
	raylib::Vector2 designerHeadingMeasurements = m_designerHeading.MeasureEx();
	m_designerHeadingPos = raylib::Vector2(
		static_cast<float>(GetScreenWidth() / 2 - designerHeadingMeasurements.x / 2),
		static_cast<float>(GetScreenHeight() * 0.1f)
	);

	m_designerText = raylib::Text(
		m_font,
		std::string("FictionalGiggle"),
		35.0f,
		1.0f,
		BLACK
	);
	raylib::Vector2 designerTextMeasurements = m_designerText.MeasureEx();
	m_designerTextPos = raylib::Vector2(
		static_cast<float>(GetScreenWidth() / 2 - designerTextMeasurements.x / 2),
		static_cast<float>(m_designerHeadingPos.y + designerHeadingMeasurements.y + headingTextYOffset)
	);

	// Fonts heading and text
	m_fontsHeading = raylib::Text(
		m_font,
		std::string("Fonts"),
		55.0f,
		1.0f,
		BLACK
	);
	raylib::Vector2 fontsHeadingMeasurements = m_fontsHeading.MeasureEx();
	m_fontsHeadingPos = raylib::Vector2(
		static_cast<float>(GetScreenWidth() / 2 - fontsHeadingMeasurements.x / 2),
		static_cast<float>(m_designerTextPos.y + designerTextMeasurements.y + sectionYOffset)
	);

	m_fontsText = raylib::Text(
		m_font,
		std::string("Mahima Khullar & Letter Art Studio"),
		35.0f,
		1.0f,
		BLACK
	);
	raylib::Vector2 fontsTextMeasurements = m_fontsText.MeasureEx();
	m_fontsTextPos = raylib::Vector2(
		static_cast<float>(GetScreenWidth() / 2 - fontsTextMeasurements.x / 2),
		static_cast<float>(m_fontsHeadingPos.y + fontsHeadingMeasurements.y + headingTextYOffset)
	);

	// SFX heading and text
	m_sfxHeading = raylib::Text(
		m_font,
		std::string("SFX"),
		55.0f,
		1.0f,
		BLACK
	);
	raylib::Vector2 sfxHeadingMeasurements = m_sfxHeading.MeasureEx();
	m_sfxHeadingPos = raylib::Vector2(
		static_cast<float>(GetScreenWidth() / 2 - sfxHeadingMeasurements.x / 2),
		static_cast<float>(m_fontsTextPos.y + fontsTextMeasurements.y + sectionYOffset)
	);

	m_sfxText = raylib::Text(
		m_font,
		std::string("DanJFilms & JuliusH"),
		35.0f,
		1.0f,
		BLACK
	);
	raylib::Vector2 sfxTextMeasurements = m_sfxText.MeasureEx();
	m_sfxTextPos = raylib::Vector2(
		static_cast<float>(GetScreenWidth() / 2 - sfxTextMeasurements.x / 2),
		static_cast<float>(m_sfxHeadingPos.y + sfxHeadingMeasurements.y + headingTextYOffset)
	);

	float buttonScale {0.8f};
	raylib::Vector2 backButtonPos {
		static_cast<float>(GetScreenWidth() / 2 - m_backButtonTexture.width * buttonScale / 2),
		static_cast<float>(GetScreenHeight() * 0.7f)
	};
	m_backButton = Button(backButtonPos, m_backButtonTexture, buttonScale);
}

void CreditsScreen::UpdateScreen(float deltaTime)
{
	// Do nothing
	if (m_backButton.isClicked())
		m_finishScreen = 1;			// Return to title screen
	
	m_backButton.update();
}

void underlineText(raylib::Text& text, raylib::Vector2& textPos)
{
	raylib::Vector2 measurements = text.MeasureEx();
	DrawLineEx(
		raylib::Vector2 {textPos.x, textPos.y + measurements.y},
		raylib::Vector2 {textPos.x + measurements.x, textPos.y + measurements.y},
		2.0f,
		BLACK
	);
}

void CreditsScreen::DrawScreen()
{
	// Draw headings and text
	
	m_designerHeading.Draw(m_designerHeadingPos, 0.0f, raylib::Vector2 {});
	underlineText(m_designerHeading, m_designerHeadingPos);
	m_designerText.Draw(m_designerTextPos, 0.0f, raylib::Vector2 {});
	
	m_fontsHeading.Draw(m_fontsHeadingPos, 0.0f, raylib::Vector2 {});
	underlineText(m_fontsHeading, m_fontsHeadingPos);
	m_fontsText.Draw(m_fontsTextPos, 0.0f, raylib::Vector2 {});

	m_sfxHeading.Draw(m_sfxHeadingPos, 0.0f, raylib::Vector2 {});
	underlineText(m_sfxHeading, m_sfxHeadingPos);
	m_sfxText.Draw(m_sfxTextPos, 0.0f, raylib::Vector2 {});

	m_backButton.draw();
}

void CreditsScreen::UnloadScreen()
{
	// Do nothing
}