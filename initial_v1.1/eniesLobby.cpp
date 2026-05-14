#include "eniesLobby.h"




//Global
int clamp(int x, int min = 0, int max = 100){
    if (x < min) return min;
    else if (x > max) return max;
    return x;
}

/*
 * BattleContext
 */
BattleContext::BattleContext() {
    turnCount = 0;
    morale = 0;
    alarmLevel = 0;
    rescueProgress = 0;
    escapeProgress = 0;
    busterCallTimer = 0;
    mainGateDestroyed = false;
    freeze = false;
    emergency = false;
    robinRescued = false;
    bridgeOpened = false;
    battleEnded = false;
    resultCode = "";
}

BattleContext::BattleContext(int morale,int alarmLevel,int rescueProgress,int escapeProgress,int busterCallTimer,int maxTurns){
    this->morale = morale;
    this->alarmLevel = alarmLevel;
    this->rescueProgress = rescueProgress;
    this->escapeProgress = escapeProgress;
    this->busterCallTimer = busterCallTimer;

}


void BattleContext::nextTurn() {
    // TODO: implement
    turnCount += 1;
}

/*
 * Character
 */
Character::Character() {
    name = "";
    hp = 0;
    maxHp = 0;
    atk = 0;
    def = 0;
    speed = 0;
    energy = 0;
    alive = false;
    skillEnergy = 0;
    killsInTurn = 0;
    isWeakest = false;
}

Character::Character(string name, int hp, int atk, int def, int speed, int energy) {
    // TODO: implement
    this->name = name;
    this->hp = hp > 0 ? hp : 0;
    this->atk = atk;
    this->def = def;
    this->speed = speed;
    this->energy = energy;
    this->maxHp = this->hp;
    this->alive = hp > 0;
    isWeakest  = false;
}

Character::~Character() {
    // TODO: implement if needed
}

bool Character::isSufficient() const{
    return energy >= skillEnergy;
}




int Character::attack(Building* target, BattleContext& context) {
    return 0;
}

int Character::specialSkill(Building* target, BattleContext& context) {
    return 0;
}

void Character::receiveDamage(int damage) {
    // TODO: implement
    int realDamage = damage - def;
    if (realDamage > 0){
        hp = clamp(hp - realDamage,0,maxHp);
    }
    setAlive();
}

bool Character::isAlive() const {
    // TODO: implement
    return alive;
}

void Character::setAlive() {
    alive = hp > 0;
}

string Character::getName() const {
    // TODO: implement
    return name;
}

bool Character::isLowestHealth() const{
    return isWeakest;
}

void Character::setLowestHealth(bool x){
    isWeakest = x;
}

int Character::getHP() const {
    // TODO: implement
    return hp;
}

void Character::setHp(int value) {
    hp = clamp(value,0, 10000);
}

int Character::getMaxHp() const{
    return maxHp;
}

int Character::getEnergy() const {
    // TODO: implement
    return energy;
}

int Character::getDef() const{
    return def;
}

int Character::getSpeed() const{
    return speed;
}

void Character::setSpeed(int value) {
    speed = clamp(value,0,100000);
}

void Character::setDef(int value){
    def = clamp(value,0, 100000);
}

bool Character::isStrawHat() const {
    return false;
}

bool Character::isCP9() const {
    return false;
}

void Character::endTurn(BattleContext& context){
    killsInTurn = 0;
    isWeakest = false;
}


/*
* StrawHat
*/
StrawHat::StrawHat() : Character() {
    bounty = 0;
    killsInTurn = 0;
}

 
StrawHat::StrawHat(string name, int hp, int atk, int def,
                   int speed, int energy, long long bounty)
                   :Character(name,hp,atk,def,speed,energy) {
    // TODO: implement
    this->bounty = bounty;
    killsInTurn = 0;
}

bool StrawHat::isStrawHat() const  {
    // TODO: implement
    return true;
}

string StrawHat::str() const {
    // TODO: implement
    string str = "StrawHat[name=" + name + ", hp=" + to_string(hp) + ", def=" + to_string(def) + ", speed=" + to_string(speed) + ", energy=" + to_string(energy) + " , bounty=" + to_string(bounty) + "]";
    
    return str;
}

/*
 * Luffy
 */
Luffy::Luffy(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty)
             :StrawHat(name,hp,atk,def,speed,energy,bounty) { 
    // TODO: implement
    skillEnergy = 20;
}
Luffy::CharType Luffy::getType() const {
    return LUFFY;
};

int Luffy::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int tempDamage = atk;
    if (hp > 0.5f * maxHp){
        tempDamage = atk;
    }
    else if (hp > 0.3f * maxHp){
        tempDamage = (int)ceil(tempDamage * 1.15f);
    }
    else {
        tempDamage = (int)ceil(tempDamage * 1.3f);
    }
    
    target->receiveDamage(tempDamage);

    
    if (!target->isAlive()){
        context.morale = clamp(context.morale +  5);
        killsInTurn += 1;
    }


    return 0;
}

int Luffy::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement


    if (!(energy >= 20 
        && hp > 0.15f * maxHp)){
            return 0;
        }
    energy -= 20;
    
    int tempDamage = 2 * atk;
    target->receiveDamage(tempDamage);

    speed += 15;
    atk += 15;

    int tempHp = hp - (int)ceil( 0.08f * maxHp);

    hp = clamp(tempHp,0,maxHp);
    context.alarmLevel = clamp(context.alarmLevel + 10);

    if (!target->isAlive()){
        context.morale = clamp(context.morale + 5);
        killsInTurn += 1;
    }
    
    return 0;
}

int Luffy::attack(Building* target, BattleContext& context) {
    // TODO: implement
    int tempDamage = atk;
    if (hp > 0.5f * maxHp){
        tempDamage = atk;
    }
    else if (hp > 0.3f * maxHp){
        tempDamage = (int)ceil(tempDamage * 1.15f);
    }
    else {
        tempDamage = (int)ceil(tempDamage * 1.3f);
    }
    
    target->receiveDamage(tempDamage);


    return 0;
}

int Luffy::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    if (!(energy >= 20 
        && hp > 0.15f * maxHp)){
            return 0;
        }
    energy -= 20;
    
    int tempDamage = 2 * atk;
    target->receiveDamage(tempDamage);

    speed += 15;
    atk += 15;

    int tempHp = hp - (int)ceil( 0.08f * maxHp);

    hp = clamp(tempHp,0,maxHp);
    context.alarmLevel = clamp(context.alarmLevel + 10);
    
    return 0;
}

void Luffy::endTurn(BattleContext& context) {
    // TODO: implement
    if (hp > 0.3f * maxHp){
        context.morale += 3;
    }
    if ( killsInTurn > 0){
        energy = clamp(energy+5);
    }
    
    //Battle Context including
    Character::endTurn(context);

}

/*
 * Zoro
 */
Zoro::Zoro(string name, int hp, int atk, int def,
           int speed, int energy, long long bounty)
           :StrawHat(name,hp,atk,def,speed,energy,bounty) {
    // TODO: implement
    skillEnergy = 15;
}

int Zoro::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int tempDamage = atk + (int)ceil(0.2f * def);
    
    if (target->getHP() < target->getMaxHp() * 0.4f){
        tempDamage = (int)ceil(tempDamage * 1.15f);
    }

    target->receiveDamage(tempDamage);
    if (!target->isAlive()){
        context.morale = clamp(context.morale + 5);

        killsInTurn += 1;

    }

    return 0;
}

int Zoro::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement

    if (!(energy >= 15)){
            return 0;
    }

    energy -= 15;

    int tempDamage = (int)ceil(2.2f * atk);
    
    if (target->getHP() < 0.5f * target->getMaxHp()){
        tempDamage = (int)ceil(tempDamage * 1.5f);
    }

    target->receiveDamage(tempDamage);
    if (!target->isAlive()){
        context.morale = clamp(context.morale + 4);

        killsInTurn += 1;
        energy = clamp(energy + 8);
    }
    

    return 0;
}
Character::CharType Zoro::getType() const{
    return ZORO;
}

int Zoro::attack(Building* target, BattleContext& context) {
    // TODO: implement
    int tempDamage = atk + (int)ceil(0.2f * def);
    
    if (target->getHP() < target->getMaxHp() * 0.4f){
        tempDamage = (int)ceil(tempDamage * 1.15f);
    }

    target->receiveDamage(tempDamage);



    return 0;
}

int Zoro::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    if (!(energy >= 15)){
            return 0;
    }

    energy -= 15;

    int tempDamage = (int)ceil(2.2f * atk);
    
    if (target->getHP() < 0.5f * target->getMaxHp()){
        tempDamage = (int)ceil(tempDamage * 1.5f);
    }

    target->receiveDamage(tempDamage);
    return 0;
}

void Zoro::endTurn(BattleContext& context) {
    // TODO: implement
    if (killsInTurn > 0){
        context.morale = clamp(context.morale + 6);
        atk = (int)ceil(atk * 1.05f);
    }
    
    Character::endTurn(context);
}

/*
 * Sanji
 */
Sanji::Sanji(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty)
             : StrawHat(name,hp,atk,def,speed,energy,bounty) {
    // TODO: implement
    skillEnergy = 18;
}
Character::CharType Sanji::getType() const{
    return SANJI;
}
int Sanji::attack(Character* target, BattleContext& context) {
    // TODO: implement
 
    int tempDamage = atk + (int)ceil(0.5f * speed);

    if (target->getDef() < def){
        tempDamage = (int)ceil(tempDamage * 1.1f);
    }

    target->receiveDamage(tempDamage);

    if (!target->isAlive()){
        context.morale = clamp(context.morale + 5);

        killsInTurn += 1;

    }
    return 0;
}

int Sanji::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    if (!(energy >= 18)){
            return 0;
    }

    energy -= 18;

    int tempDamage = (int)ceil(2.1f * atk);
    target->receiveDamage(tempDamage);
    return 0;
}

int Sanji::attack(Building* target, BattleContext& context) {
    // TODO: implement
        
    if(target->isDestroyed()){
        return 0;
    }
    int tempDamage = atk + (int)ceil(0.5f * speed);

    target->receiveDamage(tempDamage);

    if (target->isDestroyed()){
        killsInTurn += 1;
    }
    
    return 0;
}

int Sanji::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
 

    if (!(energy >= 18)){
            return 0;
    }

    energy -= 18;

    int tempDamage = (int)ceil(2.1f * atk);
    


    target->receiveDamage(tempDamage);
    
    if (target->getType() == Character::JABRA){
        target->setDef(target->getDef() - 12);
    }
    else{
        target->setDef(target->getDef() - 8);
    }

    if (!target->isAlive()){
        killsInTurn += 1;
    }
    return 0;
}

void Sanji::endTurn(BattleContext& context) {
    // TODO: implement
    if (killsInTurn > 0){
        context.morale = clamp(context.morale + 8);
        atk = (int)ceil(atk * 1.1f);
    }

    Character::endTurn(context);
}

/*
 * Nami
 */
Character::CharType Nami::getType() const{
    return NAMI;
}

Nami::Nami(string name, int hp, int atk, int def,
           int speed, int energy, long long bounty)
           :StrawHat(name,hp,atk,def,speed,energy,bounty) {
    // TODO: implement
    skillEnergy = 20;
}

int Nami::attack(Character* target, BattleContext& context) {
    // TODO: implement
    int tempDamage = atk + (int)ceil(0.3f * target->getDef());

    target->receiveDamage(tempDamage);

    if (!target->isAlive()){
        killsInTurn += 1;
    }

    return 0;
}

int Nami::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
 

    if (!(energy >= 20)){
            return 0;
    }

    energy -= 20;

    int tempDamage = atk + 40;

    target->receiveDamage(tempDamage);
    target->setSpeed(target->getSpeed() - 10);

    if (!target->isAlive()){
        killsInTurn += 1;
    }

    context.busterCallTimer += 1;
    context.alarmLevel = clamp(context.alarmLevel -5);
    return 0;
}

int Nami::attack(Building* target, BattleContext& context) {
    // TODO: implement
 
    int tempDamage = (int)ceil( atk * 0.5f);

    target->receiveDamage(tempDamage);
 

    return 0;
}

int Nami::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement

    if (!(energy >= 20)){
            return 0;
    }

    energy -= 20;

    int tempDamage = atk + 40;
    tempDamage = (int)ceil(tempDamage * 1.5f);
    target->receiveDamage(tempDamage);


    if (target->isDestroyed()){
        //Set to destroyed
    }

    context.busterCallTimer += 1;
    context.alarmLevel = clamp(context.alarmLevel -5);
    return 0;
}

void Nami::endTurn(BattleContext& context) {
    // TODO: implement
    if(killsInTurn >0){
        context.morale = clamp(context.morale + 5);
        energy = clamp(energy + 6);
    }
    Character::endTurn(context);
}

/*
 * Chopper
 */
Chopper::Chopper(string name, int hp, int atk, int def,
                 int speed, int energy, long long bounty)
                 : StrawHat ( name,hp,atk,def,speed,energy,bounty) {
    // TODO: implement
    skillEnergy = 15;
}

int Chopper::attack(Character* target, BattleContext& context) {
    // TODO: implement
 
    target->receiveDamage(atk);
    if (!target->isAlive()){
        killsInTurn += 1;
    }
    
    return 0;
}

int Chopper::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    //To the lowest health member

    if (!(energy >= 15)){
        return 0;
    }

    energy -= 15;

    int heal =  35 + (int)ceil(0.5f * atk);
    target->setHp(target->getHP() + heal);

    if (target->getType() == Character::LUFFY){
        context.morale = clamp(context.morale + 5);
    }

    return 0;
}

int Chopper::attack(Building* target, BattleContext& context) {
    // TODO: implement
 
    
    target->receiveDamage(atk);

    return 0;
}

void Chopper::endTurn(BattleContext& context) {
    return;
}

Character::CharType Chopper::getType() const{
    return CHOPPER;
}

/*
 * Usopp
 */
Character::CharType Usopp::getType() const{
    return USOPP;
}

Usopp::Usopp(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty) 
             : StrawHat(name,hp,atk,def,speed,energy,bounty){
    // TODO: implement
    skillEnergy = 16;
}

int Usopp::attack(Character* target, BattleContext& context) {
    // TODO: implement
 
    int tempDamage = atk;
    if(target->getSpeed()){
        tempDamage = (int)ceil(tempDamage * 1.2f);
    }

    target->receiveDamage(tempDamage);
    if (!target->isAlive()){
        killsInTurn += 1;
    }
    
    return 0;
}

int Usopp::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement

 
    if (energy < 16) return 0;

    energy -= 16;


    int tempDamage = (int)ceil(0.8f * atk);
    
    target->setSpeed(target->getSpeed() - 12);
    context.escapeProgress = clamp(context.escapeProgress + 4);
    target->receiveDamage(tempDamage);
    if (!target->isAlive()){
        killsInTurn += 1;
    }

    return 0;
}

int Usopp::attack(Building* target, BattleContext& context) {
    // TODO: implement
 

    int tempDamage = (int)ceil(0.5f * atk);
    
    target->receiveDamage(tempDamage);


    
    return 0;
}

int Usopp::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement

    if (target->isDestroyed()){
        return 0;
    }

    if (energy < 16) return 0;

    energy -= 16;


    int tempDamage = (int)ceil(0.8f * atk);
    context.escapeProgress = clamp(context.escapeProgress + 4);
    

    target->receiveDamage(tempDamage);
    return 0;
}

void Usopp::endTurn(BattleContext& context) {
    // TODO: implement
    context.morale = clamp(context.morale + 10);
}

/*
 * Franky
 */
Character::CharType Franky::getType() const(){
    return FRANKY;
}

Franky::Franky(string name, int hp, int atk, int def,
               int speed, int energy, long long bounty)
               : StrawHat(name,hp,atk,def,speed,energy,bounty) {
    // TODO: implement
    skillEnergy1 = 20;
    skillEnergy2 = 30;
}



int Franky::isSufficientSkill() const{
    if (energy >= skillEnergy2){
        return 2;
    }
    else if(energy >= skillEnergy1){
        return 1;
    }
}

bool Franky::isSufficient() const{
    return energy >= 20;
}


int Franky::attack(Character* target, BattleContext& context) {
    // TODO: implement
  
    int tempDamage = atk + (int)ceil(0.3f * def);
    tempDamage = (int)ceil(tempDamage * 1.1f);
 
    target->receiveDamage(tempDamage);

    if (!target->isAlive()){
        killsInTurn += 1;
    }

    return 0;
}

int Franky::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
 
    if (isSufficientSkill() == 1){    
        if (energy < 20) return 0;
        energy -= 20;
        int tempDamage = (int)ceil(1.8f * atk);
        target->setSpeed(target->getSpeed() - 8);
        if (target->getType() == LUCCI){
            tempDamage = (int)ceil(tempDamage * 1.2f);
        }
        target->receiveDamage(tempDamage);
        if (!target->isAlive()){
            killsInTurn += 1;
        }
    }
    else if (isSufficientSkill() == 2){
        if (energy < 30) return 0;
        energy -= 30;
        int tempDamage = (int)ceil(1.2f * atk);
        target->receiveDamage(tempDamage);
        if (!target->isAlive()){
            killsInTurn += 1;
        }
    }

    return 0;
}




int Franky::attack(Building* target, BattleContext& context) {
    // TODO: implement
    int tempDamage = atk + (int)ceil(0.3f * def);
 
    target->receiveDamage(tempDamage);
 
    return 0;
}

int Franky::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement

    //Skill 1
    if (isSufficientSkill() == 1){
        if (energy < 20) return 0;
        energy -= 20;
        int tempDamage = (int)ceil(1.8f * atk);
        target->receiveDamage(tempDamage);
    }

    //Skill 2
    if (isSufficientSkill() == 2){
        if (energy < 30) return 0;
        energy -= 30;
        target->receiveDamage(target->getMaxHp());
    }
    return 0;
}

void Franky::endTurn(BattleContext& context) {
    // TODO: implement
    if ( hp > 0.7f * maxHp){
        def += 5;
    }
    else if(hp < 0.3f * maxHp){
        atk = (int)ceil(atk * 1.1f);
    }
    if (killsInTurn > 0 ){
        context.morale = clamp(context.morale + 5);
    }
}

/*
 * CP9Agent
 */
CP9Agent::CP9Agent() : Character() {
    doriki = 0;
}

CP9Agent::CP9Agent(string name, int hp, int atk, int def,
                   int speed, int energy, int doriki)
                   :Character(name,hp,atk,def,speed,energy) {
    // TODO: implement
    this->doriki = doriki;
}

bool CP9Agent::isCP9() const {
    // TODO: implement
    return true;
}

Character::CharType CP9Agent::getClan() const{
    return CP9;
}

string CP9Agent::str() const {
    // TODO: implement
    string str = "CP9[name=" + name + ", hp=" + to_string(hp) + ", def=" + to_string(def) + ", speed=" + to_string(speed) + ", energy=" + to_string(energy) + " , doriki=" + to_string(doriki) + "]";

    return str;
}

/*
 * Lucci
 */
Character::CharType Lucci::getType() const{
    return LUCCI;
}

Lucci::Lucci(string name, int hp, int atk, int def,
             int speed, int energy, int doriki)
             :CP9Agent(name,hp,atk,def,speed,energy,doriki) {
    // TODO: implement
    skillEnergy = 25;
}

int Lucci::attack(Character* target, BattleContext& context) {
    // TODO: implement
 

    int tempDamage = atk + (int)ceil( 0.05 * doriki);
    if (target->getHP() < 0.5f * target->getMaxHp()){
        tempDamage = (int)ceil(tempDamage * 1.2f);
    }
    target->receiveDamage(tempDamage);
    if (!target->isAlive()) context.morale = clamp(context.morale - 5);

    return 0;
}

int Lucci::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
 
    if (energy < 25) return 0;

    energy -= 25;
    int tempDamage = (int)ceil(2.8f * atk + 0.5f * target->getDef());

    target->receiveDamage(tempDamage);
    if(!target->isAlive()){
        context.morale = clamp(context.morale - 15);
    }


    return 0;
}

void Lucci::endTurn(BattleContext& context) {
    // TODO: implement
    if (hp < 0.4f * maxHp){
        atk = (int)ceil(atk * 1.05f);
    }
}

/*
 * Kaku
 */
Character::CharType Kaku::getType() const{
    return KAKU;
}

Kaku::Kaku(string name, int hp, int atk, int def,
           int speed, int energy, int doriki)
           :CP9Agent(name,hp,atk,def,speed,energy,doriki) {
    // TODO: implement
    skillEnergy = 20;
}

int Kaku::attack(Character* target, BattleContext& context) {
    // TODO: implement
 
    target->receiveDamage(atk);

    if (!target->isAlive()) context.morale = clamp(context.morale - 5);

    return 0;
 
}

int Kaku::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
 
    if (energy < 20) return 0;

    energy -= 20;
    int tempDamage = 3 * atk;
    //Temporary
    target->receiveDamage(tempDamage);
    if(!target->isAlive()){
        context.morale = clamp(context.morale - 5);
    }
    return 0;
}

void Kaku::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Jabra
 */
Character::CharType Jabra::getType() const{
    return JABRA;
}

Jabra::Jabra(string name, int hp, int atk, int def,
             int speed, int energy, int doriki)
             :CP9Agent(name,hp,atk,def,speed,energy,doriki) {
    // TODO: implement
    skillEnergy = 18;
}

int Jabra::attack(Character* target, BattleContext& context) {
    // TODO: implement
    target->receiveDamage(atk);

    if (!target->isAlive()) context.morale = clamp(context.morale - 5);

 
    return 0;
}

int Jabra::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
 
    if (energy < 18) return 0;

    energy -= 18;
    int tempDamage = (int)ceil(atk * 1.5f);
    
    if(hp < 0.3f * maxHp){
        tempDamage = (int)ceil(tempDamage * 1.25f);
    }

    target->receiveDamage(tempDamage);
    if(!target->isAlive()){
        context.morale = clamp(context.morale - 10);
    }
    return 0;
}

void Jabra::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Blueno
 */
Character::CharType Blueno::getType() const{
    return BLUENEO;
}

Blueno::Blueno(string name, int hp, int atk, int def,
               int speed, int energy, int doriki)
                : CP9Agent(name, hp,atk,def,speed,energy,doriki) {
    // TODO: implement 
    skillEnergy = 15;
}

int Blueno::attack(Character* target, BattleContext& context) {
    // TODO: implement
    target->receiveDamage(atk);

    if (!target->isAlive()) context.morale = clamp(context.morale - 5);
    return 0;
}

int Blueno::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
 
    if (energy < 15) return 0;

    energy -= 15;
    int tempDamage = (int)ceil(atk * 1.3f);
    
    if(hp > 0.5f * maxHp){
        tempDamage = (int)ceil(tempDamage + 20);
    }
    else {
        tempDamage = tempDamage + 40;
    }

    target->receiveDamage(tempDamage);
    if(!target->isAlive()){
        context.morale = clamp(context.morale - 5);
    }
    return 0;
}

void Blueno::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Kalifa
 */
Character::CharType Kalifa::getType() const{
    return KALIFA;
}

Kalifa::Kalifa(string name, int hp, int atk, int def,
               int speed, int energy, int doriki)
               : CP9Agent(name,hp,atk,def,speed,energy,doriki) {
    // TODO: implement
    skillEnergy = 18;
}

int Kalifa::attack(Character* target, BattleContext& context) {
    // TODO: implement
 
 
    target->receiveDamage(atk);

    if (!target->isAlive()) context.morale = clamp(context.morale - 5);

 
    return 0;
}

int Kalifa::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement 
    if (energy < 18) return 0;

    energy -= 18;
    int tempDamage = (int)ceil(atk * 1.4f);
    
    if (target->getType() == Character::NAMI){
        context.morale = clamp(context.morale - 4);
    }
    context.morale = clamp(context.morale - 4);

    target->setSpeed(target->getSpeed() - 6);

    target->receiveDamage(tempDamage);
    if(!target->isAlive()){
        context.morale = clamp(context.morale - 10);
    }

    return 0;
}

void Kalifa::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Kumadori
 */
Character::CharType Kumadori::getType() const{
    return KUMADORI;
}
Kumadori::Kumadori(string name, int hp, int atk, int def,
                   int speed, int energy, int doriki)
                   :CP9Agent(name,hp,atk,def,speed,energy,doriki) {
    // TODO: implement
    skillEnergy = 16;
}

int Kumadori::attack(Character* target, BattleContext& context) {
    // TODO: implement
 
    target->receiveDamage(atk);

    if (!target->isAlive()) context.morale = clamp(context.morale - 5);

 
    return 0;
}

int Kumadori::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
   
    if (energy < 16) return 0;

    energy -= 16;
    int tempDamage = 30 + (int)ceil(0.1f * doriki);
    
    if (hp < 0.4f * maxHp){
        tempDamage += 25;
    }

    target->receiveDamage(tempDamage);
    if(!target->isAlive()){
        context.morale = clamp(context.morale - 5);
    }


    return 0;
}

void Kumadori::endTurn(BattleContext& context){
    // TODO: implement
}

/*
 * Fukurou
 */
Character::CharType Fukurou::getType() const{
    return FUKUROU;
}

Fukurou::Fukurou(string name, int hp, int atk, int def,
                 int speed, int energy, int doriki)
                 : CP9Agent(name,hp,atk,def,speed,energy,doriki) {
    // TODO: implement
    skillEnergy = 14;
}

int Fukurou::attack(Character* target, BattleContext& context) {
    // TODO: implement
 
    target->receiveDamage(atk);

    if (!target->isAlive()) context.morale = clamp(context.morale - 5);

 
    return 0;
}

int Fukurou::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
 
    if (energy < 14) return 0;

    energy -= 14;
    int tempDamage =(int)ceil(1.3f * atk);
    
    if(target->isLowestHealth()){
        tempDamage += 20;
    }

    target->receiveDamage(tempDamage);
    if(!target->isAlive()){
        context.morale = clamp(context.morale - 11);
    }


    return 0;

}

void Fukurou::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Building
 */
Building::Building(string name, int hp) {
    // TODO: implement
    this->name = name;
    this->hp = (hp >0) ? hp : 0;
    this->maxHP =this->hp;
    this->destroyed = hp <= 0;
}

Building::~Building() {
    // TODO: implement if needed
}

void Building::receiveDamage(int damage) {
    hp = hp - damage > 0 ? hp - damage : 0;
    destroyed  = hp <= 0;   
}

int Building::getHP() const{
    return hp;
}

int Building::getMaxHp() const {
    return maxHP;
}

bool Building::isDestroyed()  {
    // TODO: implement
    destroyed = hp <= 0;
    return destroyed;
}

void Building::onDestroyed(BattleContext& context) {
    return ;
}

string Building::str () const {
    // TODO: implement
    string str = "Building[name=" + name + ", hp=" + to_string(hp) + ", maxHP=" + to_string(maxHP) + ", destroyed=" + (destroyed? "true" : "false") +"]";

    return str;
}

/*
 * MainGate
 */
MainGate::MainGate(string name, int hp) : Building(name, hp) {}

Building::BuildingType MainGate::getType() const{
    return MAINGATE;
}

void MainGate::applyEffect(BattleContext& context) {
    // TODO: implement

    if (hp <= 0)
        context.freeze = true;
    else{
        context.freeze = false;
    }
    //rescueProgress không tăng
}

void MainGate::onDestroyed(BattleContext& context) {
    // TODO: implement
    
    context.mainGateDestroyed = true;
    context.rescueProgress = clamp(context.rescueProgress + 20);
    context.morale = clamp(context.morale + 5);

}

/*
 * Courthouse
 */
Courthouse::Courthouse(string name, int hp) : Building(name, hp) {}

void Courthouse::applyEffect(BattleContext& context) {
    // TODO: implement
    if(!destroyed){
        context.alarmLevel = clamp(context.alarmLevel + 5);
    }


}

void Courthouse::onDestroyed(BattleContext& context) {
    // TODO: implement
    context.alarmLevel = clamp(context.alarmLevel - 20);
    // Không tăng nữa
}
Building::BuildingType Courthouse::getType() const{
    return COURTHOUSE;
}


/*
 * TowerOfJustice
 */
TowerOfJustice::TowerOfJustice(string name, int hp) : Building(name, hp) {}

void TowerOfJustice::applyEffect(BattleContext& context) {
    // TODO: implement

    if ( context.freeze == false){
        if (context.mainGateDestroyed && !context.robinRescued){
            context.rescueProgress = clamp(context.rescueProgress + 5);
        }}
    if (context.rescueProgress >= 100){
        context.robinRescued = true;
        context.morale = clamp(context.morale + 10);
    }
}

Building::BuildingType TowerOfJustice::getType() const{ 
    return TOWEROFJUSTICE;
}
/*
 * BridgeOfHesitation
 */
BridgeOfHesitation::BridgeOfHesitation(string name, int hp) : Building(name, hp){}

void BridgeOfHesitation::applyEffect(BattleContext& context) {
    // TODO: implement
    if ( context.robinRescued){
        context.bridgeOpened = true;
        context.escapeProgress = clamp(context.escapeProgress + 5);
    }
    if (context.escapeProgress >= 100){
        context.battleEnded = true;
        context.resultCode = "STRAW_HAT_WIN";
    }
}
Building::BuildingType BridgeOfHesitation::getType() const{
    return BRIDGEOFHESITATION;
}

/*
 * BusterCallShip
 */
BusterCallShip::BusterCallShip(string name, int hp) : Building(name, hp) {}

Building::BuildingType BusterCallShip::getType() const{
    return BUSTERCALLSHIP;
}

void BusterCallShip::applyEffect(BattleContext& context) {
    // TODO: implement
    if(!destroyed){
        context.busterCallTimer -= 1;
    }
    if (context.busterCallTimer <= 0){
        context.battleEnded = true;
        context.resultCode = "BUSTER_CALL";
    }
}

void BusterCallShip::onDestroyed(BattleContext& context) {
    // TODO: implement

    context.busterCallTimer += 3;
    
}

/*
* EniesLobbyBattle
*/

EniesLobbyBattle::EniesLobbyBattle(const string& filename) {
    // TODO: implement
    strawHats = new Character*[7];
    cp9Agents = new Character*[7];
    buildings = new Building*[5];
    strawHatCount=0;
    cp9Count = 0;
    buildingCount = 0;



    loadFromFile(filename);
    return;
}

void EniesLobbyBattle::loadFromFile(const string& filename) {
    // TODO: implement
    ifstream Init(filename);
    Init.clear();
    Init.seekg(0);
    
    string type;
    int StrawHatI = 0, CP9AgentI = 0, BuildingI = 0;
    while (Init >> type){

        if (type == "CONTEXT"){
            int morale, rescueProgress,escapeProgress, busterCallTimer, maxTurns, alarmLevel;
            Init >> morale >> alarmLevel >> rescueProgress >> escapeProgress >> busterCallTimer >> maxTurns;

            context = BattleContext(morale,alarmLevel,rescueProgress,escapeProgress,busterCallTimer,maxTurns);
        }
        else if (type == "STRAW_HAT"){
            string name;
            int hp, atk, speed,def, energy, bounty;
            Init >> name >> hp >> atk >> def >> speed >> energy >> bounty;
            
            if (name == "Luffy"){
                strawHats[StrawHatI] = new Luffy(name,hp,atk,def,speed,energy,bounty);
            }
            else if (name == "Zoro"){
                strawHats[StrawHatI] = new Zoro(name,hp,atk,def,speed,energy,bounty);
            }
            else if (name == "Sanji"){
                strawHats[StrawHatI] = new Sanji(name,hp,atk,def,speed,energy,bounty);
            }
            else if (name == "Nami"){
                strawHats[StrawHatI] = new Nami(name,hp,atk,def,speed,energy,bounty);
            }
            else if (name == "Usopp"){
                strawHats[StrawHatI] = new Usopp(name,hp,atk,def,speed,energy,bounty);
            }
            else if (name == "Chopper"){
                strawHats[StrawHatI] = new Chopper(name,hp,atk,def,speed,energy,bounty);
            }
            else if (name == "Franky"){
                strawHats[StrawHatI] = new Franky(name,hp,atk,def,speed,energy,bounty);
            }
            StrawHatI ++;
            
        }
        else if (type == "CP9"){
            string name;
            int hp, atk, speed,def, energy, doriki;
            Init >> name >> hp >> atk >> def >> speed >> energy >> doriki;
            
            if (name == "Lucci"){
                cp9Agents[CP9AgentI] = new Lucci(name,hp,atk,def,speed,energy,doriki);
            }
            else if (name == "Kaku"){
                cp9Agents[CP9AgentI] = new Kaku(name,hp,atk,def,speed,energy,doriki);
            }
            else if (name == "Jabra"){
                cp9Agents[CP9AgentI] = new Jabra(name,hp,atk,def,speed,energy,doriki);
            }
            else if (name == "Blueno"){
                cp9Agents[CP9AgentI] = new Blueno(name,hp,atk,def,speed,energy,doriki);
            }
            else if (name == "Kalifa"){
                cp9Agents[CP9AgentI] = new Kalifa(name,hp,atk,def,speed,energy,doriki);
            }
            else if (name == "Kumadori"){
                cp9Agents[CP9AgentI] = new Kumadori(name,hp,atk,def,speed,energy,doriki);
            }
            else if (name == "Fukurou"){
                cp9Agents[CP9AgentI] = new Fukurou(name,hp,atk,def,speed,energy,doriki);
            }
            CP9AgentI ++;
            
            
        }
        else if (type == "BUILDING"){
            string name;
            int hp;
            Init >> name >> hp;
            if (name == "MainGate"){
                buildings[BuildingI] = new MainGate(name,hp);
            }
            else if (name == "Courthouse"){
                buildings[BuildingI] = new Courthouse(name,hp);
            }
            else if (name == "TowerOfJustice"){
                buildings[BuildingI] = new TowerOfJustice(name,hp);
            }
            else if (name == "BridgeOfHesitation"){
                buildings[BuildingI] = new BridgeOfHesitation(name,hp);
            }
            else if (name == "BusterCallShip"){
                buildings[BuildingI] = new BusterCallShip(name,hp);
            }
            BuildingI++;
        }
}
    buildingCount = BuildingI;
    cp9Count = CP9AgentI;
    strawHatCount = StrawHatI;

    buildTurnOrder();
}







EniesLobbyBattle::~EniesLobbyBattle() {
    // TODO: implement
    for (int i = 0; i < 7;i++){
        delete strawHats[i];
        delete cp9Agents[i];
        if (i< 5) delete buildings[i];
    }

    delete[] strawHats;
    delete[] cp9Agents;
    delete[] buildings;


    while(turnOrder){
        TurnNode* tempNode = turnOrder;
        turnOrder = turnOrder->next;
        delete tempNode;
    }
}

void EniesLobbyBattle::addStrawHat(Character* character) {
    // TODO: implement
    
}

void EniesLobbyBattle::addCP9Agent(Character* character) {
    // TODO: implement
}

void EniesLobbyBattle::addBuilding(Building* building) {
    // TODO: implement
}

void EniesLobbyBattle::buildTurnOrder() {
    // TODO: implement
    turnOrder = nullptr;
    TurnNode* newNode = nullptr;
    TurnNode* tempNode = nullptr;
    int i =0;

    while(strawHats[i] != nullptr){
        newNode = new TurnNode{strawHats[i], nullptr};

        if (turnOrder == nullptr){
            turnOrder = newNode;
            turnOrder = newNode;
        }
        else{
            tempNode->next = newNode;
            tempNode = newNode;
        }
        i++;
    }
    i =0;
    while(cp9Agents[i] != nullptr){
        newNode = new TurnNode{cp9Agents[i], nullptr};

        if (turnOrder == nullptr){
            turnOrder = newNode;
            turnOrder = newNode;
        }
        else{
            tempNode->next = newNode;
            tempNode = newNode;
        }
        i++;
    }
}

void EniesLobbyBattle::runBattle() {
    // TODO: implement
    TurnNode* tempNode = turnOrder;
    while (!context.battleEnded && context.turnCount < maxTurns ){
        TurnNode* toAction = tempNode;
        if (tempNode == nullptr){
            tempNode = turnOrder;
            continue;
        }

        tempNode = tempNode->next;
        //Xử lí vòng, khi kết thúc vòng thì quay lại như cũ
        if (!toAction->data->isAlive()){
            continue;
        }


        //Attack của nhân vật
        processTurn(toAction->data);
        processBuildings();
        context.turnCount += 1;
        checkEndCondition();
    }
    
    if (!context.battleEnded){
        context.battleEnded = true;
        context.resultCode = "TIME_OUT";
    }

}

void EniesLobbyBattle::processTurn(Character* character) {
    // TODO: implement
    Building* targetB = chooseBuilding();
    if(targetB != nullptr){
        // Đủ năng lượng => thực hiện skill, else, tấn công thường
        if (character->isSufficient() != Character::getType() != Character::CHOPPER){
            character->specialSkill(targetB,context);
        } 
        else{
            character->attack(targetB,context);

        }
        if (targetB->isDestroyed()){
            targetB->onDestroyed(context);
        }
    }

    else if (targetB == nullptr){
        if (character->isStrawHat()){
            if (character->getType() == Character::CHOPPER)
                //if đủ năng lượng mới thực hiện, không thì vẫn là như cũ
                if (character->isSufficient()){
                    Character* targetC = chooseCharacterForChopper();
                    character->specialSkill(targetC,context);
                }
                else{
                    Character* targetC = chooseCharacterForStrawHats();
                    character->attack(targetC,context);
                }

            else{
                if ( character->isSufficient()){
                    Character* targetC = chooseCharacterForStrawHats();
                    character->specialSkill(targetC,context);
                }
                else {
                    Character* targetC = chooseCharacterForStrawHats();
                    character->attack(targetC,context);
                }
            }
        }
        else if (character->isCP9()){
            //Call to find the lowest Health member:
            Character* targetC = chooseCharacterForChopper();
            targetC = chooseCharacterForCP9();
            
            if ( character->isSufficient()){
                character->specialSkill(targetC, context);
            }
            else {
                character->attack(targetC,context);
            }
        }
    }
    character->endTurn(context);

}




Building* EniesLobbyBattle::chooseBuilding(){
    int i = 0 ;

    while (buildings[i]){
        if(buildings[i]->getType() == Building::MAINGATE){
            if (!buildings[i]->isDestroyed()){
                return buildings[i];
            }
        }
        else if(buildings[i]->getType() == Building::COURTHOUSE){
            if (!buildings[i]->isDestroyed()){
                if (context.alarmLevel >= 50){
                    return buildings[i];
                }
            }
        }
        else if(buildings[i]->getType() == Building::BUSTERCALLSHIP){
            if (!buildings[i]->isDestroyed()){
                if (context.BusterCallShip <= 5){
                    return context.BusterCallShip;
                }
            }
        }
        else if(context.robinRescued){
            if (!buildings[i]->getType() == Building::BRIDGEOFHESITATION){
                if (!buildings[i]->isDestroyed()){
                    return buildings[i];
                }
                else{
                    return nullptr;
                }
            }
        }
        i++;
    }
    return nullptr;
}


Character* EniesLobbyBattle::chooseCharacterForChopper(){
    int i = 0;
    int minHp = strawHats[0]->getHP();
    Character* tempTarget = strawHats[0];
    while(strawHats[i]){
        if (strawHats[i]->getHP() < minHp  && strawHats[i]->isAlive()){
            tempTarget = strawHats[i];
            minHp =  strawHats[i]->getHP();
        }
        i++;
    }
    return tempTarget;
}


Character* EniesLobbyBattle::chooseCharacterForStrawHats(){

    Building* temp = chooseBuilding();
    if ((!context.robinRescued && temp == nullptr) || (context.robinRescued && temp == nullptr)){
        int i = 0;
        while (!cp9Agents[i]->isAlive()){
            i++;
        }    
        if (cp9Agents[i] != nullptr) return cp9Agents[i];
        else return nullptr;
    }
}

Character* EniesLobbyBattle::chooseCharacterForCP9(){
    int i = 0;
    while (!strawHats[i]->isAlive()){
        i++;
    }    
    if (strawHats[i] != nullptr) return strawHats[i];
    else return nullptr;
}



 
void EniesLobbyBattle::processBuildings() {
    // TODO: implement
    int i =0;
    while(buildings[i]){
        if(!buildings[i]->isDestroyed()){
            buildings[i]->applyEffect(context);
        }
        i++;
    }
}

void EniesLobbyBattle::checkEndCondition() {
    // TODO: implement
    if (context.robinRescued && context.escapeProgress >= 100){
        context.resultCode = "STRAW_HAT_WIN";
        return;
    }
    else if (context.busterCallTimer <= 0){
        context.resultCode = "BUSTER_CALL";
        return;
    }
    else if (context.turnCount >= maxTurns){
        context.resultCode = "TIME_OUT";
        return;
    }

    bool strawAlive = false;
    bool cp9ALive = false;
    
    for (int i = 0; i < strawHatCount ; i++){
        if (strawHats[i] != nullptr){
            strawAlive = true;
            break;
        }
    }
    for (int i = 0; i < cp9Count ; i++){
        if (cp9Agents[i] != nullptr){
            cp9ALive = true;
            break;
        }
    }

    if (!strawAlive) {
        context.resultCode = "CP9_WIN";
        return;
    }
    else if (!cp9ALive){
        context.resultCode = "STRAW_HAT_WIN_BY_DEFEAT_CP9";
        return;
    }


    

}

string EniesLobbyBattle::getResult() const {
    // TODO: implement
    string str = context.resultCode + " " + to_string(context.turnCount) + " " + to_string(context.morale) + " " + to_string(context.alarmLevel) + " " + to_string(context.rescueProgress) + " " + to_string(context.escapeProgress) + " " + to_string(context.busterCallTimer);
    return str;
}


