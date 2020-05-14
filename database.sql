CREATE TABLE IF NOT EXISTS "snmpSignals"(id serial primary key, signalValue text not null, time timestamp default current_timestamp);

INSERT INTO "snmpSignals" (signalValue) values ('sig 1');
INSERT INTO "snmpSignals" (signalValue) values ('sig 2');
INSERT INTO "snmpSignals" (signalValue) values ('sig 3');
INSERT INTO "snmpSignals" (signalValue) values ('sig 4');
INSERT INTO "snmpSignals" (signalValue) values ('sig 5');

