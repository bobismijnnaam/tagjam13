// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 10-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <memory>

// Private
#include "game/CloudManager.hpp"
#include "main/functions.hpp"
#include "main/global.hpp"
#include "nnb/log/log.hpp"

CloudManager::CloudManager() :
cloudTexture(IMG_LoadTexture(g_renderer, "media/sprites/cloud.png")),
rainTexture(IMG_LoadTexture(g_renderer, "media/sprites/rain.png")) {

}

CloudManager::~CloudManager() {
	SDL_DestroyTexture(cloudTexture);
	SDL_DestroyTexture(rainTexture);
}

void CloudManager::launchCloud() {
	if (frozen) return;
		
	std::string word = words[randfloat() * words.size()];
	clouds.push_back(std::unique_ptr<Cloud>(new Cloud(word, cloudTexture, rainTexture, proFontMedium)));
}

float CloudManager::getWaterLvl() const {
	return waterLvl;
}

int CloudManager::getTypedWords() const {
	return clearedClouds;
}

void CloudManager::event(SDL_Event &e) {

}

void CloudManager::logic(TypeTracker &ttracker, float dt) {
	std::vector<int> doneClouds;
	int activeClouds = 0;
	
	for (Uint32 i = 0; i < clouds.size(); i++) {
		Cloud* tCloud = clouds[i].get();

		CloudState prevState = tCloud->getState();
		tCloud->logic(ttracker);

		if (tCloud->getState() == CloudState::LEAVING && prevState != CloudState::LEAVING) {
			ttracker.clear();
			clearedClouds++;
			NNB_LOG << "Cleared a cloud. Clouds cleared: " << clearedClouds;

			// Pump a little bit of water away!
			waterLvl -= 0.05;
		} else if (tCloud->getState() == CloudState::DONE) {
			doneClouds.push_back(i);
		}

		if (tCloud->getState() == CloudState::RAINING || tCloud->getState() == CloudState::STORMY) {
			activeClouds++;
		}
	}

	for (int i = doneClouds.size() - 1; i >= 0; i--) {
		clouds.erase(clouds.begin() + doneClouds[i]);
		NNB_LOG << "Deleted a cloud";
	}

	// waterLvl += pow(sqrt(activeClouds) * dt, 2); // Old formula
	// New formula!
	if (activeClouds > 0) {
		waterLvl += pow((3.5 + 6 / (-1.8 - activeClouds)) * dt, 2);
	}

	if (waterLvl >= 5.8) {
		frozen = true;
	}
}

void CloudManager::render(SDL_Renderer *tgt) const {
	for (Uint32 i = 0; i < clouds.size(); i++) {
		Cloud* tCloud = clouds[i].get();

		tCloud->render();
	}
}
