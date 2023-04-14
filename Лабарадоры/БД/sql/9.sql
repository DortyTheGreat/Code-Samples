create table jobs(
	id integer primary key AUTO_INCREMENT, 
    name varchar(50),
    salary integer
);

insert into jobs (name, salary) values
('Менеджер', 80000 ),
('Водитель', 50000 ),
('Инженер', 60000 ),
('Механик', 60000 ),
('Курьер', 50000 );

select * from jobs;




create table employees(
	id integer primary key AUTO_INCREMENT, -- код сотрудника
    name varchar(50), -- Имя
	BirthDate date,
    gender varchar(10),
    phone varchar(15),
    job_id integer
);

-- Добавляем контент в первую таблицу
insert into employees (name, BirthDate, gender, phone, job_id) 
values 
('Кулешов Александр Сергеевич', '2003-04-30', 'Мужчина', '+71231234545', 2),
('Кулешов Михаил Сергеевич', '2003-06-25', 'Мужчина', '+71228234545', 3),
('Тогузов Дмитрий Васильевич', '2002-05-29', 'Мужчина', '+71223456545', 4),
('Попова Ольга Дмитриевна', '1999-04-27', 'Женщина', '+71200004545', 5),
('Попова Кристина Дмитриевна', '1980-03-12', 'Женщина', '+71200007775', 2),
('Попова Кристина Дмитриевна', '1985-02-13', 'Женщина', '+71200007775', 1);
-- Запрос, посмотрим таблицу фильмов
select * from employees;

drop table employees;


create table auto_models(
	id integer primary key AUTO_INCREMENT,
    name varchar(50), 
	horse_power integer
);

insert into auto_models (name, horse_power)
values
('Kia Rio', 100),
('Hyundai Solaris', 123),
('Ford Mondeo', 130),
('Chery Bonus Hatchback', 108),
('Peogeot 307', 109);

select * from auto_models;



create table autos(
	id integer primary key AUTO_INCREMENT, -- код сотрудника
    registration_num integer,
    model_id integer,
    model_year integer,
    mileage integer, -- в км
	price_auto integer, -- в рублях
    rent_price integer -- в рублях
);

insert into autos(registration_num, model_id, model_year, mileage, price_auto, rent_price) values
(456678, 1, 2006, 123456, 500000, 1800),
(456211, 2, 2001, 200000, 600000, 2000),
(413456, 2, 2000, 220000, 520000, 1900),
(453456, 3, 1998, 120000, 470000, 1700),
(498756, 3, 2001, 125000, 500000, 2100),
(398456, 4, 1991, 200000, 600000, 2200),
(947021, 5, 2000, 230000, 600000, 1600);

select * from autos;



create table clients(
	id integer primary key AUTO_INCREMENT,
    name varchar(50), 
	gender varchar(10),
    phone varchar(15),
    address varchar(50),
    passport varchar(100),
    BirthDate date
);

insert into clients(name, BirthDate, gender, phone, address, passport) values
('Кулешов Александр Сергеевич', '2003-04-30', 'Мужчина', '+71231234545', 'Тверская улица, дом 13', '4507-691234-772-050'),
('Кулешов Михаил Сергеевич', '2003-06-25', 'Мужчина', '+71228234545', 'Тверская улица, дом 15','1234-874234-122-450'),
('Тогузов Дмитрий Васильевич', '2002-05-29', 'Мужчина', '+71223456545', '119049 г. Москва, ул. Донская, д. 8 стр. 1', '4123-698734-721-120'),
('Попова Ольга Дмитриевна', '1999-04-27', 'Женщина', '+71200004545', 'Проспект вернадского, 43, кв 29', '4507-691234-772-050'),
('Попова Кристина Дмитриевна', '1999-03-12', 'Женщина', '+71200007775', 'Улица Стандартная, дом 21 корпус корп.1', '7492-920142-714-924'),
('Попова Кристина Дмитриевна', '1999-02-13', 'Женщина', '+71200007775', 'Новорязанская ул., д. 38.', '037288-920164-937-824');

select * from clients;




create table rent(
	auto_id integer,
    client_id integer,
    receive_date date,
    return_date date,
    return_state varchar(20),
    job_id integer
);

-- '2022-04-14' сегодня
insert into rent(auto_id, client_id, receive_date, return_date, return_state, job_id) values
(1,1, '2022-04-12', '2022-04-28', 'используется', 5),
(2,3, '2022-04-01', '2022-04-8', 'возвращена', 1),
(2,3, '2022-04-12', '2022-04-14', 'обслуживание', 1),
(3,4, '2022-04-11', '2022-04-19', 'неизвестно', 2),
(3,5, '2022-04-22', '2022-04-25', 'запланировано', 4),
(4,2, '2022-04-11', '2022-04-29', 'используется', 3);
select * from rent;




-- ЗАДАНИЕ №1. Сотрудники, которые старше 25
select * from employees
where DATEDIFF(CURDATE(), BirthDate) > 365*25;


-- Задание №2(?). Вывести автопарк со всеми реквизитами
select * from autos;


-- Задание №3. Вывести те авто, что сейчас в прокате
select * from rent where return_state='используется';


-- Задание №4. Вывести те авто, что не были возвращены
select * from rent where return_state='неизвестно' or return_state='используется';

-- Задание №5. Вывести те авто, что были возвращены (с кучей доп. данных)
select * from rent where return_state='возвращена';


-- Задание №6. 3 самых популярных авто
SELECT auto_id, COUNT(*) AS popularity
FROM rent AS r
GROUP BY r.auto_id
ORDER BY popularity DESC
LIMIT 3;


-- Задание №7. Количество авто на работника
select job_id, count(*) from rent as r
group by r.job_id