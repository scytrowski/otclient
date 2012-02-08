/*
 * Copyright (c) 2010-2012 OTClient <https://github.com/edubart/otclient>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef GAME_H
#define GAME_H

#include "declarations.h"
#include <otclient/net/declarations.h>
#include <otclient/core/item.h>
#include <otclient/core/outfit.h>
#include <framework/core/timer.h>

class Game
{
public:
    Game();

private:
    void resetGameStates();

protected:

    /*
    void parseMapDescription(InputMessage& msg);
    void parseMapMoveNorth(InputMessage& msg);
    void parseMapMoveEast(InputMessage& msg);
    void parseMapMoveSouth(InputMessage& msg);
    void parseMapMoveWest(InputMessage& msg);
    void parseUpdateTile(InputMessage& msg);
    void parseTileAddThing(InputMessage& msg);
    void parseTileTransformThing(InputMessage& msg);
    void parseTileRemoveThing(InputMessage& msg);
    void parseCreatureMove(InputMessage& msg);

    void parseOpenContainer(InputMessage& msg);
    void parseCloseContainer(InputMessage& msg);
    void parseContainerAddItem(InputMessage& msg);
    void parseContainerUpdateItem(InputMessage& msg);
    void parseContainerRemoveItem(InputMessage& msg);

    void parseAddInventoryItem(InputMessage& msg);
    void parseRemoveInventoryItem(InputMessage& msg);

    void parseNpcOffer(InputMessage& msg);
    void parsePlayerCash(InputMessage& msg);
    void parseCloseShopWindow(InputMessage&);

    void parseWorldLight(InputMessage& msg);

    void parseMagicEffect(InputMessage& msg);
    void parseAnimatedText(InputMessage& msg);
    void parseDistanceMissile(InputMessage& msg);

    void parseCreatureSquare(InputMessage& msg);
    void parseCreatureHealth(InputMessage& msg);
    void parseCreatureLight(InputMessage& msg);
    void parseCreatureOutfit(InputMessage& msg);
    void parseCreatureSpeed(InputMessage& msg);
    void parseCreatureSkulls(InputMessage& msg);
    void parseCreatureShields(InputMessage& msg);
    void parseCreatureTurn(InputMessage& msg);

    void parseItemTextWindow(InputMessage& msg);
    void parseHouseTextWindow(InputMessage& msg);
    void parsePlayerStats(InputMessage& msg);
    void parsePlayerSkills(InputMessage& msg);
    void parsePlayerIcons(InputMessage& msg);
    void parsePlayerCancelAttack(InputMessage& msg);
    void parseCreatureSpeak(InputMessage& msg);
    void parseCloseChannel(InputMessage& msg);
    void parseSafeTradeRequest(InputMessage& msg);
    void parseSafeTradeClose(InputMessage&);
    void parseTextMessage(InputMessage& msg);
    void parseCancelWalk(InputMessage& msg);
    void parseFloorChangeUp(InputMessage& msg);
    void parseFloorChangeDown(InputMessage& msg);
    void parseOutfitWindow(InputMessage& msg);
    void parseShowTutorial(InputMessage& msg);
    void parseAddMarker(InputMessage& msg);
    */

    void processConnectionError(const boost::system::error_code& error);
    void processDisconnect();
    void processPing();

    void processLoginError(const std::string& error);
    void processLoginAdvice(const std::string& message);
    void processLoginWait(const std::string& message, int time);

    void processLogin();
    void processLogout();

    void processGameStart(const LocalPlayerPtr& localPlayer, int serverBeat);
    void processGameEnd();
    void processDeath(int penality);

    void processPlayerStats(double health, double maxHealth,
                            double freeCapacity, double experience,
                            double level, double levelPercent,
                            double mana, double maxMana,
                            double magicLevel, double magicLevelPercent,
                            double soul, double stamina);
    void processTextMessage(const std::string& type, const std::string& message);
    void processCreatureSpeak(const std::string& name, int level, Otc::SpeakType type, const std::string& message, int channelId, const Position& creaturePos);

    void processOpenContainer(int containerId, int itemId, const std::string& name, int capacity, bool hasParent, const std::vector<ItemPtr>& items);
    void processContainerAddItem(int containerId, const ItemPtr& item);

    void processInventoryChange(int slot, const ItemPtr& item);
    void processCreatureMove(const CreaturePtr& creature, const Position& oldPos, const Position& newPos);
    void processCreatureTeleport(const CreaturePtr& creature);
    void processAttackCancel();
    void processWalkCancel(Otc::Direction direction);

    // processChannelList
    // processOpenChannel
    // processOpenPrivateChannel
    // processOpenOwnPrivateChannel

    // vip
    // processVipList
    // processVipLogin
    // processVipLogout

    // processQuestLog
    // processQuestLine

    friend class ProtocolGame;
    friend class Map;

public:
    // login related
    void loginWorld(const std::string& account,
                    const std::string& password,
                    const std::string& worldHost, int worldPort,
                    const std::string& characterName);
    void cancelLogin();
    void forceLogout();
    void safeLogout();

    // walk related
    void walk(Otc::Direction direction);
    void walkPath(const std::vector<Otc::Direction>& dir);
    void forceWalk(Otc::Direction direction);
    void turn(Otc::Direction direction);
    void stop();

    // item related
    void look(const ThingPtr& thing);
    void move(const ThingPtr &thing, const Position& toPos, int count);
    void rotate(const ThingPtr& thing);
    void use(const ThingPtr& thing);
    void useWith(const ItemPtr& fromThing, const ThingPtr& toThing);
    void useInventoryItem(int itemId);
    void useInventoryItemWith(int itemId, const ThingPtr& toThing);

    // container related
    void open(const ItemPtr& item, int containerId);
    void upContainer(int containerId);
    void refreshContainer();

    // attack/follow related
    void attack(const CreaturePtr& creature);
    void cancelAttack() { attack(nullptr); }
    void follow(const CreaturePtr& creature);
    void cancelFollow() { follow(nullptr); }
    void cancelAttackAndFollow();

    // talk related
    void talk(const std::string& message);
    void talkChannel(Otc::SpeakType speakType, int channelId, const std::string& message);
    void talkPrivate(Otc::SpeakType speakType, const std::string& receiver, const std::string& message);

    // channel related
    void openPrivateChannel(const std::string& receiver);
    void requestChannels();
    void joinChannel(int channelId);
    void leaveChannel(int channelId);
    void closeNpcChannel();
    void openOwnChannel();
    void inviteToOwnChannel(const std::string& name);
    void excludeFromOwnChannel(const std::string& name);

    // party related
    void partyInvite(int creatureId);
    void partyJoin(int creatureId);
    void partyRevokeInvitation(int creatureId);
    void partyPassLeadership(int creatureId);
    void partyLeave();
    void partyShareExperience(bool active);

    // outfit related
    void requestOutfit();
    void changeOutfit(const Outfit& outfit);

    // vip related
    void addVip(const std::string& name);
    void removeVip(int playerId);

    // fight modes related
    void setChaseMode(Otc::ChaseModes chaseMode);
    void setFightMode(Otc::FightModes fightMode);
    void setSafeFight(bool on);
    Otc::ChaseModes getChaseMode() { return m_chaseMode; }
    Otc::FightModes getFightMode() { return m_fightMode; }
    bool isSafeFight() { return m_safeFight; }

    // npc trade related
    //void inspectNpcTrade();
    //void buyItem();
    //void sellItem();
    //void closeNpcTrade();

    // player trade related
    //void requestTrade();
    //void inspectTrade();
    //void acceptTrade();
    //void rejectTrade();

    // house window and editable items related
    //void editText();
    //void editList();

    // questlog related
    //void requestQuestLog();
    //void requestQuestLogLine();

    bool canPerformGameAction();
    bool checkBotProtection();

    bool isOnline() { return !!m_localPlayer; }
    bool isDead() { return m_dead; }
    bool isAttacking() { return !!m_attackingCreature; }
    bool isFollowing() { return !!m_followingCreature; }

    CreaturePtr getAttackingCreature() { return m_attackingCreature; }
    CreaturePtr getFollowingCreature() { return m_followingCreature; }
    int getServerBeat() { return m_serverBeat; }
    LocalPlayerPtr getLocalPlayer() { return m_localPlayer; }
    ProtocolGamePtr getProtocolGame() { return m_protocolGame; }
    int getProtocolVersion() { return PROTOCOL; }

private:
    void setAttackingCreature(const CreaturePtr& creature);
    void setFollowingCreature(const CreaturePtr& creature);

    LocalPlayerPtr m_localPlayer;
    CreaturePtr m_attackingCreature;
    CreaturePtr m_followingCreature;
    ProtocolGamePtr m_protocolGame;
    bool m_dead;
    int m_serverBeat;
    Otc::FightModes m_fightMode;
    Otc::ChaseModes m_chaseMode;
    bool m_safeFight;
};

extern Game g_game;

#endif
