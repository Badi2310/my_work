ADD jar /opt/cloudera/parcels/CDH/lib/hive/lib/hive-serde.jar;
ADD jar /opt/cloudera/parcels/CDH/lib/hive/lib/hive-contrib.jar;


SET hive.exec.dynamic.partition.mode=nonstrict;
SET hive.exec.max.dynamic.partitions.pernode=300;
SET hive.exec.max.dynamic.partitions=1200;


USE badigulaj;

DROP TABLE IF EXISTS TempLogs;
CREATE EXTERNAL TABLE TempLogs (
	ip STRING,
	request_date STRING,
	request STRING,
	page_size INT,
	http_status INT,
	info STRING
)
ROW FORMAT SERDE 'org.apache.hadoop.hive.serde2.RegexSerDe'
WITH SERDEPROPERTIES (
    "input.regex" = '^(\\S*)\\t{3}(\\d{8})\\S*\\t(\\S*)\\t(\\d*)\\t(\\d*)\\t(\\S*).*$'
)
STORED AS TEXTFILE
LOCATION '/data/user_logs/user_logs_M';


DROP TABLE IF EXISTS Logs;
CREATE EXTERNAL TABLE Logs(
	ip STRING,
	request STRING,
	page_size INT,
	http_status INT,
	info STRING
)
PARTITIONED BY (request_date STRING)
STORED AS TEXTFILE;
INSERT OVERWRITE TABLE Logs PARTITION(request_date)
SELECT ip, request, page_size, http_status, info, request_date FROM TempLogs;
SELECT * FROM Logs LIMIT 10;


DROP TABLE IF EXISTS Users;
CREATE EXTERNAL TABLE Users(
  ip STRING,
  browser STRING,
  sex STRING,
  age INT
)
ROW FORMAT SERDE 'org.apache.hadoop.hive.serde2.RegexSerDe'
WITH SERDEPROPERTIES(
  "input.regex" = '^(\\S*)\\t(\\S*)\\t(\\S*)\\t(\\d*)$'
)
STORED AS TEXTFILE
LOCATION '/data/user_logs/user_data_M';
select *
from Users
limit 10;


DROP TABLE IF EXISTS IPRegions;
CREATE EXTERNAL TABLE IPRegions(
  ip STRING,
  region STRING
)
ROW FORMAT SERDE 'org.apache.hadoop.hive.serde2.RegexSerDe'
WITH SERDEPROPERTIES(
  "input.regex" = '^(\\S*)\\t(.*)$'
)
STORED AS TEXTFILE
LOCATION '/data/user_logs/ip_data_M';
select *
from IPRegions
limit 10;


DROP TABLE IF EXISTS Subnets;
CREATE EXTERNAL TABLE Subnets(
  ip STRING,
  mask STRING
)
ROW FORMAT SERDE 'org.apache.hadoop.hive.serde2.RegexSerDe'
WITH SERDEPROPERTIES(
  "input.regex" = '^(\\S*)\\t(\\S*)$'
)
STORED AS TEXTFILE
LOCATION '/data/subnets/variant2';
select *
from Subnets
limit 10;
