ADD jar /opt/cloudera/parcels/CDH/lib/hive/lib/hive-serde.jar;
ADD jar /opt/cloudera/parcels/CDH/lib/hive/lib/hive-contrib.jar;

USE badigul_test;

SELECT 
  browser,
  sum(CASE WHEN sex = 'male' THEN 1
       WHEN sex = 'female' THEN 0
  END),
  sum(CASE WHEN sex = 'male' THEN 0
       WHEN sex = 'female' THEN 1
  END)
from Users
GROUP BY browser
limit 10
