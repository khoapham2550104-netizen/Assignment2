#include "eniesLobby.h"

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
}

Character::~Character() {
    // TODO: implement if needed
}

void Character::clampStats(){
    hp = clamp(hp,0,maxHp);
    energy = clamp(energy);

    setAlive();
}

void Character::clamp(int x, int min = 0, int max = 100){
    if (x < min) return min;
    else if (x > max) return max;
    return x;
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
        hp = this->clamp(hp - realDamage,0,maxHp);
    }
    this->setAlive();
}

bool Character::isAlive() const {
    // TODO: implement
    return alive;
}

void Character::setAlive() {
    this->alive = hp > 0;
}

string Character::getName() const {
    // TODO: implement
    return name;
}

int Character::getHP() const {
    // TODO: implement
    return hp;
}
int character::getMaxHp() const{
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

void Character::setSpeed(int value) const {
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

bool StrawHat::isStrawHat() const override {
    // TODO: implement
    return true;
}

string StrawHat::str() const {
    // TODO: implement
    string str = "StrawHat[name=" + name + ", hp=" + to_string(hp) + ", def=" + to_string(def) + ", speed=" + to_string(speed) + ", energy=" + to_string(energy) + " , bounty=" + to_string(bounty) + "]";
    
    return "";
}

/*
 * Luffy
 */
Luffy::Luffy(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty)
             :StrawHat(name,hp,atk,def,speed,energy,bounty) { 
    // TODO: implement
}
Luffy::CharType getType() const override{
    return LUFFY;
};

int Luffy::attack(Character* target, BattleContext& context) {
    // TODO: implement
    if(!target->isAlive()){
        return 0;
    }


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
        context.morale = clamp(context..morale +  5);
        killsInTurn += 1;
    }


    return 0;
}

int Luffy::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    if(!target->isAlive()){
        return 0;
    }


    if (!(energy >= 20 
        && hp > 0.15f * maxHp)){
            return;
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
        context.morale = clamp(context.morale + 5)
        killsInTurn += 1;
    }
    
    return 0;
}

int Luffy::attack(Building* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Luffy::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
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
}

int Zoro::attack(Character* target, BattleContext& context) {
    // TODO: implement
    if(!target->isAlive()){
        return 0;
    }


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

    if(!target->isAlive()){
        return 0;
    }

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
Zoro::CharType getType() const{
    return ZORO;
}

int Zoro::attack(Building* target, BattleContext& context) {
    // TODO: implement

    return 0;
}

int Zoro::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
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
}
Sanji::CharType getType() const{
    return SANJI;
}
int Sanji::attack(Character* target, BattleContext& context) {
    // TODO: implement
    
    if(!target->isAlive()){
        return 0;
    }
    int tempDamage = atk * (int)ceil(0.5f * speed);

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
    
    return 0;
}

int Sanji::attack(Building* target, BattleContext& context) {
    // TODO: implement
        
    if(target->isDestroyed()){
        return 0;
    }
    int tempDamage = atk + (int)ceil(0.5f * speed);

    target->receiveDamage(tempDamage);

    if (!target->isAlive()){
        killsInTurn += 1;
    }
    
    return 0;
}

int Sanji::specialSkill(Character
    * target, BattleContext& context) {
    // TODO: implement
    if(!target->isAlive()){
        return 0;
    }

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
Nami::CharType getType() const{
    return NAMI;
}

Nami::Nami(string name, int hp, int atk, int def,
           int speed, int energy, long long bounty)
           :StrawHat(name,hp,atk,def,speed,energy,bounty) {
    // TODO: implement
}

int Nami::attack(Character* target, BattleContext& context) {
    // TODO: implement
    if(!target->isAlive()){
        return 0;
    }
    int tempDamage = atk + (int)ceil(0.3f * target->getDef());

    target->receiveDamage(tempDamage);

    if (!target->isAlive()){
        killsInTurn += 1;
    }

    return 0;
}

int Nami::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    if(!target->isAlive()){
        return 0;
    }

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
    if(target->isDestroyed()){
        return 0;
    }
    int tempDamage = (int)ceil( atk * 0.5f);

    target->receiveDamage(tempDamage);
    if (target->isDestroyed()){
        //Set target destroyed in class building
    }

    return 0;
}

int Nami::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    if(target->isDestroyed()){
        return 0;
    }

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
}

int Chopper::attack(Character* target, BattleContext& context) {
    // TODO: implement
    if (!target->isAlive()){
        return 0;
    }
    target->receiveDamage(atk);
    if (target->isAlive()){
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
    if (!target->isDestroyed()){
        return 0;
    }
    
    target->receiveDamage(atk);

    return 0;
}

void Chopper::endTurn(BattleContext& context) {
    // TODO: implement
    return;
}

Chopper::CharType getType() const{
    return CHOPPER;
}

/*
 * Usopp
 */
Usopp::getType() const{
    return USOPP;
}

Usopp::Usopp(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty) 
             : StrawHat(name,hp,atk,def,speed,energy,bounty){
    // TODO: implement
    
}

int Usopp::attack(Character* target, BattleContext& context) {
    // TODO: implement
    if (!target->isAlive()){
        return 0;
    }
    int tempDamage = atk;
    if(target->getSpeed()){
        tempDamage = (int)ceil(tempDamage * 1.2f);
    }

    target->receiveDamage(tempDamage);
    if (target->isAlive()){
        killsInTurn += 1;
    }
    
    return 0;
}

int Usopp::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement

    if (!target->isAlive()){
        return 0;
    }
    if (energy < 16) return 0;

    energy -= 16


    int tempDamage = (int)ceil(0.8f * atk);
    
    target->setSpeed(target->getSpeed() - 12);

    target->receiveDamage(tempDamage);
    if (target->isAlive()){
        killsInTurn += 1;
    }

    return 0;
}

int Usopp::attack(Building* target, BattleContext& context) {
    // TODO: implement
    if (target->isDestroyed()){
        return 0;
    }

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

    energy -= 16


    int tempDamage = (int)ceil(0.8f * atk);
    

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
Franky::CharType getType(){
    return FRANKY;
}

Franky::Franky(string name, int hp, int atk, int def,
               int speed, int energy, long long bounty)
               : StrawHat(name,hp,atk,def,speed,energy,bounty) {
    // TODO: implement
}

int Franky::attack(Character* target, BattleContext& context) {
    // TODO: implement
    
    
    if (!target->isAlive()){
        return 0;
    }
 


    int tempDamage = atk + (int)ceil(0.3f * def);
    if (target->isCP9()) tempDamage = (int)ceil(tempDamage * 1.1f);
 
    target->receiveDamage(tempDamage);

    if (target->isAlive()){
        killsInTurn += 1;
    }

    return 0;
}

int Franky::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    
    if (!target->isAlive()){
        return 0;
    }

    //Skill 1
    if (energy < 20) return 0;
    energy -= 20;
    int tempDamage = (int)ceil(1.8f * atk);
    target->setSpeed(target->getSpeed() - 8);
    if (target->getType() == LUCCI){
        tempDamage = (int)ceil(tempDamage * 1.2f);
    }
    target->receiveDamage(tempDamage);
    if (target->isAlive()){
        killsInTurn += 1;
    }

    //Skill 2
    if (energy < 30) return 0;
    energy -= 30;
    int tempDamage = (int)ceil(1.2f * atk);
    target->receiveDamage(tempDamage);
    if (target->isAlive()){
        killsInTurn += 1;
    }


    return 0;
}

int Franky::attack(Building* target, BattleContext& context) {
    // TODO: implement
    return 0;
}

int Franky::specialSkill(Building* target, BattleContext& context) {
    // TODO: implement
    if (target->isDestroyed()){
        return 0;
    }

    //Skill 1
    if (energy < 20) return 0;
    energy -= 20;
    int tempDamage = (int)ceil(1.8f * atk);
    target->receiveDamage(tempDamage);
    if (target->isAlive()){
        killsInTurn += 1;
    }

    //Skill 2
    if (energy < 30) return 0;
    energy -= 30;


    target->receiveDamage(target->getMaxHp());



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

string CP9Agent::str() const {
    // TODO: implement
    string str = "CP9[name=" + name + ", hp=" + to_string(hp) + ", def=" + to_string(def) + ", speed=" + to_string(speed) + ", energy=" + to_string(energy) + " , doriki=" + to_string(doriki) + "]";

    return "";
}

/*
 * Lucci
 */
Lucci::CharType getType(){
    return LUCCI;
}

Lucci::Lucci(string name, int hp, int atk, int def,
             int speed, int energy, int doriki)
             :CP9Agent(name,hp,atk,def,speed,energy,doriki) {
    // TODO: implement
}

int Lucci::attack(Character* target, BattleContext& context) {
    // TODO: implement
    if (!target->isAlive()){
        return 0;
    }

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
    if (!target->isAlive())return 0;
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
Kaku::CharType getType(){
    return KAKU;
}

Kaku::Kaku(string name, int hp, int atk, int def,
           int speed, int energy, int doriki)
           :CP9Agent(name,hp,atk,def,speed,energy,doriki) {
    // TODO: implement
}

int Kaku::attack(Character* target, BattleContext& context) {
    // TODO: implement
    if (!target->isAlive()){
        return 0;
    }

 
    target->receiveDamage(atk);

    if (!target->isAlive()) context.morale = clamp(context.morale - 5);

    return 0;
 
}

int Kaku::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    if (!target->isAlive())return 0;
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
Jabra::CharType getType(){
    return JABRA;
}

Jabra::Jabra(string name, int hp, int atk, int def,
             int speed, int energy, int doriki)
             :CP9Agent(name,hp,atk,def,speed,energy,doriki) {
    // TODO: implement
}

int Jabra::attack(Character* target, BattleContext& context) {
    // TODO: implement
    if (!target->isAlive()){
        return 0;
    }

 
    target->receiveDamage(atk);

    if (!target->isAlive()) context.morale = clamp(context.morale - 5);

 
    return 0;
}

int Jabra::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    if (!target->isAlive())return 0;
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
Blueno::CharType getType(){
    return BLUENEO;
}

Blueno::Blueno(string name, int hp, int atk, int def,
               int speed, int energy, int doriki)
                : CP9Agent(name, hp,atk,dè,speed,energy,doriki) {
    // TODO: implement 
}

int Blueno::attack(Character* target, BattleContext& context) {
    // TODO: implement
    if (!target->isAlive()){
        return 0;
    }

 
    target->receiveDamage(atk);

    if (!target->isAlive()) context.morale = clamp(context.morale - 5);

 
   
    return 0;
}

int Blueno::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    if (!target->isAlive())return 0;
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
Kalifa::CharType getType(){
    return KALIFA;
}

Kalifa::Kalifa(string name, int hp, int atk, int def,
               int speed, int energy, int doriki)
               : CP9Agent(name,hp,atk,def,speed,energy,doriki) {
    // TODO: implement
}

int Kalifa::attack(Character* target, BattleContext& context) {
    // TODO: implement
    if (!target->isAlive()){
        return 0;
    }

 
    target->receiveDamage(atk);

    if (!target->isAlive()) context.morale = clamp(context.morale - 5);

 
    return 0;
}

int Kalifa::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    if (!target->isAlive())return 0;
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
Kumadori::CharType getType(){
    return KUMADORI;
}
Kumadori::Kumadori(string name, int hp, int atk, int def,
                   int speed, int energy, int doriki)
                   :CP9Agent(name,hp,atk,def,speed,energy,doriki) {
    // TODO: implement
}

int Kumadori::attack(Character* target, BattleContext& context) {
    // TODO: implement
    if (!target->isAlive()){
        return 0;
    }

 
    target->receiveDamage(atk);

    if (!target->isAlive()) context.morale = clamp(context.morale - 5);

 
    return 0;
}

int Kumadori::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    if (!target->isAlive())return 0;
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

void Kumadori::endTurn(BattleContext& context) {
    // TODO: implement
}

/*
 * Fukurou
 */
Fukurou::CharType getType(){
    return FUKUROU;
}

Fukurou::Fukurou(string name, int hp, int atk, int def,
                 int speed, int energy, int doriki) {
    // TODO: implement
}

int Fukurou::attack(Character* target, BattleContext& context) {
    // TODO: implement
    if (!target->isAlive()){
        return 0;
    }

 
    target->receiveDamage(atk);

    if (!target->isAlive()) context.morale = clamp(context.morale - 5);

 
    return 0;
}

int Fukurou::specialSkill(Character* target, BattleContext& context) {
    // TODO: implement
    if (!target->isAlive())return 0;
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
    this->hp = hp;
}

Building::~Building() {
    // TODO: implement if needed
}

void Building::receiveDamage(int damage) {
    hp = hp - damage > 0 ? hp - damage : 0;
    destroyed  = hp > 0;   
}

int Building::getMaxHp() const {
    return maxHP;
}

bool Building::isDestroyed() const {
    // TODO: implement
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

void MainGate::applyEffect(BattleContext& context) {
    // TODO: implement
    if (!destroyed)
        context.freeze = true;
    else{
        context.freeze = false;
    }
    //rescueProgress không tăng
}

void MainGate::onDestroyed(BattleContext& context) {
    // TODO: implement
    
    if (destroyed) {
        context.mainGateDestroyed = true;
        context.rescueProgress = clamp(context.rescueProgress + 20);
        context.morale = clamp(context.morale + 5);
    }
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
    if(destroyed) context.alarmLevel = clamp(context.alarmLevel - 20);
}

/*
 * TowerOfJustice
 */
TowerOfJustice::TowerOfJustice(string name, int hp) : Building(name, hp) {}

void TowerOfJustice::applyEffect(BattleContext& context) {
    // TODO: implement
    if (context.mainGateDestroyed && !context.robinRescued){
        context.rescueProgress = clamp(context.rescueProgress + 5);
    }
    if (context.rescueProgress >= 100){
        context.robinRescued = true;
        context.morale = clamp(context.morale + 10);
    }
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

/*
 * BusterCallShip
 */
BusterCallShip::BusterCallShip(string name, int hp) : Building(name, hp) {}

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
    if(destroyed){
        context.busterCallTimer += 3;
    }
}

/*
 * EniesLobbyBattle
 */
EniesLobbyBattle::EniesLobbyBattle(const string& filename) {
    // TODO: implement
    ifstream Init(filename);
    Init.clear();
    Init.seekg(0);

    string type;
    int StrawHatI = 0, CP9AgentI = 0, BuildingI = 0;
    while (Init >> type){

    if (type == "CONTEXT"){
        int morale, rescueProgress,escapeProgress, busterCallTimer, maxTurns;
        Init >> morale >> rescueProgress >> escapeProgress >> busterCallTimer >> maxTurns;

        context = BattleContext(morale,alarmLevel,rescueProgress,escapeProgress,busterCallTimer,maxTurns);
    }
    else if (type == "STRAW_HAT"){
        
    }
    else if (type == "CP9"){}
    else if (type == "BUILDING"){}
}







    Init.close();
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
}

void EniesLobbyBattle::loadFromFile(const string& filename) {
    // TODO: implement
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
}

void EniesLobbyBattle::runBattle() {
    // TODO: implement
}

void EniesLobbyBattle::processTurn(Character* character) {
    // TODO: implement
}

void EniesLobbyBattle::processBuildings() {
    // TODO: implement
}

void EniesLobbyBattle::checkEndCondition() {
    // TODO: implement
}

string EniesLobbyBattle::getResult() const {
    // TODO: implement
    return "";
}