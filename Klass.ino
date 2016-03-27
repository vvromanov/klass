#include <LiquidCrystal.h> //объявление экрана

#define LCD_PINS 8, 9, 3, 5, 6, 7 //объявление пинов 
LiquidCrystal lcd(LCD_PINS); //интерфейс к экрану

#define CLASS_COUNT 3000 // количество проверяемых классов
#define MIN_CLASS_SIZE 1 //минимальный размер класса
#define MAX_CLASS_SIZE 100 //максимальный размер класса
#define DAYS_COUNT 365 // количество дней в году


bool test_class(uint16_t class_size) { //возращает тру если есть дни рождения в один день
  bool bds[DAYS_COUNT]; // есть ли у кого-то день рождения в этот день
  for (uint16_t i=0;i<DAYS_COUNT;i++) { //обнуляем
    bds[i]=false; 
  }
  for (uint16_t kid_number=0;kid_number<class_size;kid_number++) {
    uint16_t bd=random(DAYS_COUNT); // выбираем учиникам свой день рождения
    if (bds[bd]==true){
      return true; // нашли совпадения
    }
    bds[bd]=true;
  }
  return false; // не нашли совпадений
}

uint32_t test_classes(uint16_t class_size, uint32_t class_count) { //возращает количество классов с совпавшими днями рождения
  uint32_t count=0; //обнуляем каунт
  for(uint32_t i=0;i<class_count;i++){
    if (test_class(class_size)) {
      count++;
    }
  }
  return count;
}

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Started");
  Serial.begin(115200);
  Serial.println("\nStarted");
}

// считаем проценты
void loop() {
  Serial.println("\n\nCount;Value");
  for (uint16_t class_size = MIN_CLASS_SIZE; class_size <= MAX_CLASS_SIZE; class_size++) {
    uint32_t count=test_classes(class_size,CLASS_COUNT);
    uint16_t promile=count*1000/CLASS_COUNT;

    // вывод на экран
    lcd.clear();
    lcd.print("Size=");
    lcd.print(class_size);
    lcd.print(" ");
    lcd.print(promile/10);
    lcd.print(".");
    lcd.print(promile%10);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print(count);
    lcd.print("/");
    lcd.print(CLASS_COUNT);

    // вывод на серийный монитор  
    Serial.print(class_size);
    Serial.print(";");
    Serial.print(promile/10);
    Serial.print(",");
    Serial.println(promile%10);
  }
}

