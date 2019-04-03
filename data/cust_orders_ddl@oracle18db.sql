-- ****************************************** Customers *****************************************
CREATE TABLE customers (
    cust_id        NUMBER(10) NOT NULL,
    cust_name      VARCHAR2(50) NOT NULL,
    website        VARCHAR2(50),
    last_modified TIMESTAMP (6) DEFAULT SYSTIMESTAMP NOT NULL,
    CONSTRAINT pk_cust_id PRIMARY KEY ( cust_id ),
    CONSTRAINT uni_cust_name UNIQUE ( cust_name )
)
TABLESPACE "USERS";
/

CREATE OR REPLACE TRIGGER customer_table_insert
 BEFORE INSERT ON customers
 FOR EACH ROW
BEGIN
    :new.cust_id := GET_NEXT_KEYVALUE('customers');
END;
/

CREATE OR REPLACE TRIGGER customers_table_timestamp
 BEFORE INSERT OR UPDATE ON customers
 FOR EACH ROW
BEGIN
 :new.last_modified := SYSTIMESTAMP;
END;
/

-- ****************************************** Addresses *****************************************
CREATE TABLE addresses (
    address_id NUMBER GENERATED ALWAYS AS IDENTITY,
    entity_id NUMBER(10) NOT NULL,
    address_line1 VARCHAR2(50) NOT NULL,
    address_line2 VARCHAR2(50) DEFAULT 'NULL' NOT NULL,
    city VARCHAR2(50) NOT NULL,
    state_code CHAR(2) NOT NULL,
    zipcode VARCHAR2(10) NOT NULL,
    last_modified TIMESTAMP (6) DEFAULT SYSTIMESTAMP NOT NULL,
    CONSTRAINT pk_address_id PRIMARY KEY ( address_id ),
    CONSTRAINT fk_address_statecode FOREIGN KEY ( state_code )
        REFERENCES state_codes ( state_code )    
)
TABLESPACE "USERS";
/
CREATE INDEX "idx_address_entityid" ON addresses ( entity_id );
/

CREATE OR REPLACE TRIGGER addresse_table_timestamp
 BEFORE INSERT OR UPDATE ON addresses
 FOR EACH ROW
BEGIN
 :new.last_modified := SYSTIMESTAMP;
END;


-- ****************************************** Telephones *****************************************
CREATE TABLE telephones
(
    telephone_id NUMBER GENERATED ALWAYS AS IDENTITY,
    entity_id NUMBER(10) NOT NULL,
    telephone_number VARCHAR2(15) NOT NULL,
    extension VARCHAR2(6) DEFAULT 'NULL' NOT NULL,
    telephone_type VARCHAR2(6) NOT NULL,
    last_modified TIMESTAMP (6) DEFAULT SYSTIMESTAMP NOT NULL,
    CONSTRAINT pk_telephone_id PRIMARY KEY ( telephone_id ),
    CONSTRAINT ck_telephone_type CHECK (telephone_type IN('CELL', 'FAX', 'OFFICE') ),
    CONSTRAINT uni_telephone_number UNIQUE ( telephone_number )
)
TABLESPACE "USERS";
/
CREATE INDEX "idx_telephone_entityid" ON telephones (entity_id);

CREATE OR REPLACE TRIGGER telephones_table_timestamp
 BEFORE INSERT OR UPDATE ON telephones
 FOR EACH ROW
BEGIN
 :new.last_modified := SYSTIMESTAMP;
END;

-- ****************************************** State_codes *****************************************
CREATE TABLE state_codes
(
    state_code CHAR(2) NOT NULL,
    state_name VARCHAR2(25) NOT NULL,
    CONSTRAINT pk_state_codes PRIMARY KEY ( state_code ),
    CONSTRAINT uni_state_name UNIQUE ( state_name )
)
TABLESPACE "USERS";
/

-- ****************************************** Orders *****************************************
CREATE TABLE orders (
    order_id        NUMBER GENERATED ALWAYS AS IDENTITY,
    cust_id         NUMBER(10) NOT NULL,
    order_date      DATE NOT NULL,
    ship_date       DATE,
    order_amt       NUMBER(8,2) DEFAULT(0.0) NOT NULL,
	last_modified TIMESTAMP (6) DEFAULT SYSTIMESTAMP NOT NULL,
    CONSTRAINT pk_orders PRIMARY KEY ( order_id ),
    CONSTRAINT fk_orders_customers FOREIGN KEY ( cust_id )
        REFERENCES customers ( cust_id )
)
TABLESPACE "USERS";
/
CREATE INDEX "IDX_order_orderdate" ON orders (order_date);
CREATE INDEX "IDX_order_shipdate" ON orders (ship_date);

CREATE TABLE shippers (
    shipper_id      NUMBER GENERATED ALWAYS AS IDENTITY,
    shipper_name    VARCHAR2(30) NOT NULL,
	last_modified TIMESTAMP (6) DEFAULT SYSTIMESTAMP NOT NULL,
    CONSTRAINT pk_shipper PRIMARY KEY ( shipper_id )
)
TABLESPACE "USERS";
/
CREATE UNIQUE INDEX "IDX_shippername_UNIQUE" ON shippers ( shipper_name );


-- ****************************************** Vendors *****************************************
CREATE TABLE vendors (
    vendor_id   NUMBER(10) NOT NULL,
    vendor_name VARCHAR2(30) NOT NULL,
    website     VARCHAR2(50),
    rating      NUMBER(3) DEFAULT 0 NOT NULL, 
    last_modified TIMESTAMP (6) DEFAULT SYSTIMESTAMP NOT NULL,
    CONSTRAINT pk_vendor_id PRIMARY KEY ( vendor_id ),
    CONSTRAINT uni_vendor_name UNIQUE ( vendor_name )
)
TABLESPACE "USERS";
/

ALTER TABLE vendors MODIFY vendor_id number(10);

CREATE OR REPLACE TRIGGER vendor_table_insert
 BEFORE INSERT ON vendors
 FOR EACH ROW
BEGIN
    :new.vendor_id := GET_NEXT_KEYVALUE('vendors');
END;
/

-- ****************************************** Inventory *****************************************
CREATE TABLE inventory (
    inventory_id    NUMBER GENERATED ALWAYS AS IDENTITY,
    vendor_id       NUMBER(10) NOT NULL,
	vendor_sku		VARCHAR2(10) NOT NULL,
    item_desc       VARCHAR2(30) NOT NULL,
    unit_cost       NUMBER(6,2) DEFAULT 0.0 NOT NULL,
    price           NUMBER(6,2) DEFAULT 0.0 NOT NULL,
    qty_on_hand     NUMBER(6) DEFAULT 0 NOT NULL,
    qty_reorder     NUMBER(6) DEFAULT 0 NOT NULL,
	item_weight_lbs NUMBER(8,4) NOT NULL,
    last_modified TIMESTAMP (6) DEFAULT SYSTIMESTAMP NOT NULL,
    CONSTRAINT pk_inventory_id PRIMARY KEY ( inventory_id ),
    CONSTRAINT uni_vendor_item UNIQUE ( vendor_id, item_desc ),
    CONSTRAINT fk_inventory_vendors FOREIGN KEY ( vendor_id )
        REFERENCES vendors ( vendor_id )    
)
TABLESPACE "USERS";
/
CREATE INDEX "IDX_inventory_qtyonhand" ON inventory (qty_on_hand);
CREATE INDEX "IDX_inventory_qtyreorder" ON inventory (qty_reorder);

-- ****************************************** Order_details *****************************************
CREATE TABLE order_details (
    orderdetail_id  NUMBER GENERATED ALWAYS AS IDENTITY,
    order_id        NUMBER(10) NOT NULL,
    inventory_id    NUMBER(10) NOT NULL,
    qty_ordered     NUMBER(6) NOT NULL,
    qty_shipped     NUMBER(6) DEFAULT 0 NOT NULL,
    last_modified TIMESTAMP (6) DEFAULT SYSTIMESTAMP NOT NULL,
    CONSTRAINT pk_orderdetail_id PRIMARY KEY ( orderdetail_id ),
    CONSTRAINT fk_orderdetails_orders FOREIGN KEY ( order_id )
        REFERENCES orders ( order_id ), 
    CONSTRAINT fk_orderdetails_inventory FOREIGN KEY ( inventory_id )
        REFERENCES inventory ( inventory_id )         
)
TABLESPACE "USERS";
/
CREATE INDEX "IDX_orderdetails_qtyordered" ON order_details (qty_ordered);
CREATE INDEX "IDX_orderdetails_qty_shipped" ON order_details (qty_shipped);

-- ****************************************** Payments *****************************************
CREATE TABLE payments (
    payment_id  NUMBER GENERATED ALWAYS AS IDENTITY,
    order_id    NUMBER(10) NOT NULL,
    pymt_date   DATE,
    pymt_amt    NUMBER(8,2) DEFAULT 0.0 NOT NULL,
    pymt_type   VARCHAR2(15) NOT NULL,
    document_num VARCHAR2(30) DEFAULT 'Not Entered' NOT NULL,
    last_modified TIMESTAMP (6) DEFAULT SYSTIMESTAMP NOT NULL,
    CONSTRAINT pk_payment_id PRIMARY KEY ( payment_id ),
    CONSTRAINT fk_payments_orders FOREIGN KEY ( order_id )
        REFERENCES orders ( order_id ),
    CONSTRAINT CK_payment_type CHECK (pymt_type IN('CASH', 'CHECK', 'CREDIT CARD', 'PURCHASE ORDER', 'RMA') )
)
TABLESPACE "USERS";
/
CREATE INDEX "IDX_pymts_date" ON payments (pymt_date);
CREATE INDEX "IDX_pymts_type" ON payments (pymt_type);

-- ****************************************** sp_load_shippers *****************************************
CREATE OR REPLACE PROCEDURE sp_load_shippers
AS
BEGIN
    INSERT INTO shippers (shipper_name, last_modified) VALUES ('UPS', SYSTIMESTAMP);
    INSERT INTO shippers (shipper_name, last_modified) VALUES ('FEDEX', SYSTIMESTAMP);
    INSERT INTO shippers (shipper_name, last_modified) VALUES ('U.S. Postal Service', SYSTIMESTAMP);   
    COMMIT WORK;
END;

-- ****************************************** sp_load_customers *****************************************
create or replace PROCEDURE sp_load_customers
AS
BEGIN
    INSERT INTO CUSTOMERS (cust_name, website, last_modified) VALUES('Fred''s Auto Shop', 'http://www.fredsautoshop.com', SYSTIMESTAMP);
    INSERT INTO CUSTOMERS (cust_name, website, last_modified) VALUES('Alex''s Music Store', 'https://www.alexmusic.com', SYSTIMESTAMP);
    INSERT INTO CUSTOMERS (cust_name, website, last_modified) VALUES('Brian''s Brain Surgery', 'https://www.brainsurgery.edu', SYSTIMESTAMP);
    COMMIT WORK;
END;

-- ****************************************** sp_load_vendors *****************************************
CREATE OR REPLACE PROCEDURE sp_load_vendors
AS
BEGIN
    INSERT INTO vendors (vendor_name, website, rating, last_modified) VALUES ('Jon Brown''s Material',  'jbrown@earthlink.com', 77, SYSTIMESTAMP);
    INSERT INTO vendors (vendor_name, website, rating, last_modified) VALUES ('Sanchez''s Supplies',  'juan@aol.com', 98, SYSTIMESTAMP);
    INSERT INTO vendors (vendor_name, website, rating, last_modified) VALUES ('Lisa''s Fabrics',  'lisa@aol.com', 99, SYSTIMESTAMP);
    INSERT INTO vendors (vendor_name, website, rating, last_modified) VALUES ('Luigi''s Inc.',  'Lu@aol.com', 45, SYSTIMESTAMP); 
    COMMIT WORK;
END;

-- ****************************************** sp_load_addresses *****************************************
create or replace PROCEDURE sp_load_addresses
AS
BEGIN
    INSERT INTO addresses (entity_id, address_line1, address_line2, city, state_code, zipcode, last_modified) VALUES (1, '123 South Main', 'Ste 10', 'Logan', 'UT', '84321', SYSTIMESTAMP);
    INSERT INTO addresses (entity_id, address_line1, address_line2, city, state_code, zipcode, last_modified) VALUES (2, '921 Rose St.', 'Dock 15A','Logan', 'UT', '84322', SYSTIMESTAMP);
    INSERT INTO addresses (entity_id, address_line1, address_line2, city, state_code, zipcode, last_modified) VALUES (3, '6574 Riverside', 'Suite 2','Chicago', 'IL', '45367', SYSTIMESTAMP);
    INSERT INTO addresses (entity_id, address_line1, address_line2, city, state_code, zipcode, last_modified) VALUES (4, '22145 Oak Street', '#22', 'Centerville', 'UT', '87543', SYSTIMESTAMP);
    INSERT INTO addresses (entity_id, address_line1, address_line2, city, state_code, zipcode, last_modified) VALUES (5, '472 South Main', 'No. 333', 'Logan', 'UT', '84321', SYSTIMESTAMP); 
    INSERT INTO addresses (entity_id, address_line1, address_line2, city, state_code, zipcode, last_modified) VALUES (6, '345 South Oak Street', 'Ste 1', 'Lyman', 'UT', '87632', SYSTIMESTAMP); 
    INSERT INTO addresses (entity_id, address_line1, address_line2, city, state_code, zipcode, last_modified) VALUES (7, '345 East Center', 'Ste 1', 'Millville', 'UT', '84563', SYSTIMESTAMP); 
    COMMIT WORK;
END;

-- ****************************************** sp_load_telephones_numbers *****************************************

create or replace PROCEDURE sp_load_telephone_numbers
AS
BEGIN
    INSERT INTO telephones (entity_id, telephone_number, extension, telephone_type, last_modified) VALUES (1, '435-745-9999', '55555', 'OFFICE', SYSTIMESTAMP); 
    INSERT INTO telephones (entity_id, telephone_number, extension, telephone_type, last_modified) VALUES (1, '435-745-9998', '55555', 'FAX', SYSTIMESTAMP);
    INSERT INTO telephones (entity_id, telephone_number, extension, telephone_type, last_modified) VALUES (2, '435-798-7374', '55555', 'OFFICE', SYSTIMESTAMP);
    INSERT INTO telephones (entity_id, telephone_number, extension, telephone_type, last_modified) VALUES (2, '435-798-3456', '55555', 'FAX', SYSTIMESTAMP); 
    INSERT INTO telephones (entity_id, telephone_number, extension, telephone_type, last_modified) VALUES (3, '756-874-0000', '55555', 'OFFICE', SYSTIMESTAMP);
    INSERT INTO telephones (entity_id, telephone_number, extension, telephone_type, last_modified) VALUES (3, '123-874-7543', '55555', 'FAX', SYSTIMESTAMP);
    INSERT INTO telephones (entity_id, telephone_number, extension, telephone_type, last_modified) VALUES (4, '456-234-1234', '55555', 'CELL', SYSTIMESTAMP);
    INSERT INTO telephones (entity_id, telephone_number, extension, telephone_type, last_modified) VALUES (4, '456-234-5678', '55555', 'FAX', SYSTIMESTAMP);
    INSERT INTO telephones (entity_id, telephone_number, extension, telephone_type, last_modified) VALUES (4, '456-234-6021', '55555', 'OFFICE', SYSTIMESTAMP);
    INSERT INTO telephones (entity_id, telephone_number, extension, telephone_type, last_modified) VALUES (5, '456-234-7845', '55555', 'OFFICE', SYSTIMESTAMP);
    INSERT INTO telephones (entity_id, telephone_number, extension, telephone_type, last_modified) VALUES (5, '456-888-6789', '55555', 'FAX', SYSTIMESTAMP);
    INSERT INTO telephones (entity_id, telephone_number, extension, telephone_type, last_modified) VALUES (6, '456-999-6789', '55555', 'CELL', SYSTIMESTAMP);
    INSERT INTO telephones (entity_id, telephone_number, extension, telephone_type, last_modified) VALUES (6, '456-202-6789', '55555', 'FAX', SYSTIMESTAMP);
    INSERT INTO telephones (entity_id, telephone_number, extension, telephone_type, last_modified) VALUES (6, '456-365-6789', '55555', 'OFFICE', SYSTIMESTAMP);
    INSERT INTO telephones (entity_id, telephone_number, extension, telephone_type, last_modified) VALUES (7, '456-111-6789', '55555', 'CELL', SYSTIMESTAMP);
    INSERT INTO telephones (entity_id, telephone_number, extension, telephone_type, last_modified) VALUES (7, '456-284-6789', '55555', 'OFFICE', SYSTIMESTAMP);    
    COMMIT WORK;
END;

-- ****************************************** sp_load_orders *****************************************
CREATE OR REPLACE PROCEDURE sp_load_orders
AS
BEGIN
INSERT INTO orders (cust_id, order_date, ship_date, order_amt, last_modified) 
    VALUES (1, TO_DATE('2018-NOV-17 00:00:00', 'YYYY-MON-DD HH24:MI:SS:SSSSS'), TO_DATE('2018-NOV-20 00:00:00', 'YYYY-MON-DD HH24:MI:SS:SSSSS'), 164.00, SYSTIMESTAMP);
INSERT INTO orders (cust_id, order_date, ship_date, order_amt, last_modified) 
    VALUES (1, TO_DATE('2018-DEC-01 00:00:00', 'YYYY-MON-DD HH24:MI:SS:SSSSS'), TO_DATE('2018-DEC-02 00:00:00', 'YYYY-MON-DD HH24:MI:SS:SSSSS'), 36.00, SYSTIMESTAMP);
INSERT INTO orders (cust_id, order_date, ship_date, order_amt, last_modified) 
    VALUES (1, TO_DATE('2019-FEB-01 00:00:00', 'YYYY-MON-DD HH24:MI:SS:SSSSS'), TO_DATE('2019-FEB-01 00:00:00', 'YYYY-MON-DD HH24:MI:SS:SSSSS'), 36.00, SYSTIMESTAMP);
INSERT INTO orders (cust_id, order_date, ship_date, order_amt, last_modified) 
    VALUES (2, TO_DATE('2018-AUG-21 00:00:00', 'YYYY-MON-DD HH24:MI:SS:SSSSS'), TO_DATE('2018-SEP-04 00:00:00', 'YYYY-MON-DD HH24:MI:SS:SSSSS'), 424.00, SYSTIMESTAMP);
INSERT INTO orders (cust_id, order_date, ship_date, order_amt, last_modified) 
    VALUES (2, TO_DATE('2018-OCT-28 00:00:00', 'YYYY-MON-DD HH24:MI:SS:SSSSS'), TO_DATE('2018-NOV-15 00:00:00', 'YYYY-MON-DD HH24:MI:SS:SSSSS'), 116.00, SYSTIMESTAMP);
INSERT INTO orders (cust_id, order_date, ship_date, order_amt, last_modified) 
    VALUES (3, TO_DATE('2019-JAN-14 00:00:00', 'YYYY-MON-DD HH24:MI:SS:SSSSS'), TO_DATE('2019-JAN-15 00:00:00', 'YYYY-MON-DD HH24:MI:SS:SSSSS'), 94.00, SYSTIMESTAMP);
COMMIT WORK;
END; 

-- ****************************************** sp_load_inventory_items *****************************************
CREATE OR REPLACE PROCEDURE sp_load_inventory_items
AS
BEGIN
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (4, '35241','Garden spade, silver', 1, 4, 123, 25, 1.1, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (4, '45000', 'Shovel, gray', 5, 18, 231, 50, 2, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (4, '78901', 'Nails, grey', 2, 6, 5000, 500, 3, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (4, '89012', 'Hammer, Fur-covered', 2.5, 7, 12, 25, 2, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (5, '33392', 'Sand, white', 10, 25, 123, 25, 100, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (5, '34567', 'Snow shovel, blue', 10, 25, 300, 75, 4.5, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (5, '45678', 'Snow blower, red', 50, 100, 33, 5, 236.1, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (5, '48573', 'Ladder, Aluminum', 20, 60, 12, 25, 15.1, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (5, '66775', 'Paint, white', 6, 20, 18, 25, 12, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (5, '86753', 'Hand saw, silver', 5, 14, 3, 15, 14, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (5, '95739', 'Flashlight, red', 1, 5, 175, 250, .6, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (5, '95740', 'Flashlight, blue', 1, 5, 198, 250, .6, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (5, '12345', 'Screwdriver', 2, 6, 62, 100, .1, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (6, '29874', 'Picture hanging kit', 1, 2.5, 51, 48, .2, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (7, '22257', 'Sand paper', .4, 2, 338, 500, .3, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (7, '23560', 'Drill, 1/4 inch', 56, 99, 9, 25, 2.7, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (7, '45068', 'Paint brush', 2, 6, 684, 1000, .3, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (7, '56789', 'Garden gloves, green', 1, 2, 87, 50, .1, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (7, '67890', 'Light Bulb, Natural light', 1, 2, 429, 1000, .1, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (7, '85947', 'Paint, brown', 6, 20, 61, 50, 12, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (7, '88574', 'Cypress Mulch', 5, 15, 35, 35, 100, SYSTIMESTAMP);
    INSERT INTO inventory (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified) VALUES (7, '90210', 'Batteries, Flashlight', 2, 6, 123, 25, 1.3, SYSTIMESTAMP);
    COMMIT WORK;
END;
/ 

-- ****************************************** sp_load_order_details *****************************************
CREATE OR REPLACE PROCEDURE sp_load_order_details
AS
BEGIN
    INSERT INTO order_details (order_id, inventory_id, qty_ordered, qty_shipped, last_modified) VALUES (1,15, 12, 12, SYSTIMESTAMP);
    INSERT INTO order_details (order_id, inventory_id, qty_ordered, qty_shipped, last_modified) VALUES (1,20, 7, 2, SYSTIMESTAMP);
    INSERT INTO order_details (order_id, inventory_id, qty_ordered, qty_shipped, last_modified) VALUES (2,2, 2, 2, SYSTIMESTAMP);
    INSERT INTO order_details (order_id, inventory_id, qty_ordered, qty_shipped, last_modified) VALUES (3,13, 5, 5, SYSTIMESTAMP);
    INSERT INTO order_details (order_id, inventory_id, qty_ordered, qty_shipped, last_modified) VALUES (4,16, 4, 3, SYSTIMESTAMP);
    INSERT INTO order_details (order_id, inventory_id, qty_ordered, qty_shipped, last_modified) VALUES (4,4, 4, 4, SYSTIMESTAMP);
    INSERT INTO order_details (order_id, inventory_id, qty_ordered, qty_shipped, last_modified) VALUES (5,13, 1, 1, SYSTIMESTAMP);
    INSERT INTO order_details (order_id, inventory_id, qty_ordered, qty_shipped, last_modified) VALUES (5,11, 22, 22, SYSTIMESTAMP);
    INSERT INTO order_details (order_id, inventory_id, qty_ordered, qty_shipped, last_modified) VALUES (6,17, 8, 0, SYSTIMESTAMP);
    INSERT INTO order_details (order_id, inventory_id, qty_ordered, qty_shipped, last_modified) VALUES (6,18, 5, 5, SYSTIMESTAMP);
    INSERT INTO order_details (order_id, inventory_id, qty_ordered, qty_shipped, last_modified) VALUES (6,4, 12, 12, SYSTIMESTAMP);
    COMMIT WORK;
END;
/

-- ****************************************** sp_load_payments *****************************************
CREATE OR REPLACE PROCEDURE sp_load_payments
AS
BEGIN
INSERT INTO payments (order_id, pymt_date, pymt_amt, pymt_type, document_num, last_modified) VALUES (1, TO_DATE('2018-NOV-17 00:00:00', 'YYYY-MON-DD HH24:MI:SS:SSSSS'), 124.00, 'CHECK', '48712', SYSTIMESTAMP);
INSERT INTO payments (order_id, pymt_date, pymt_amt, pymt_type, document_num, last_modified) VALUES (6, TO_DATE('2019-JAN-14 00:00:00', 'YYYY-MON-DD HH24:MI:SS:SSSSS'), 94.00, 'CHECK', '9871', SYSTIMESTAMP);
COMMIT WORK;
END;
/

-- ****************************************** sp_test_data_setup *****************************************
create or replace PROCEDURE sp_test_data_setup
AS
BEGIN
    DELETE FROM payments;
    DELETE FROM order_details;
    DELETE FROM inventory;
    DELETE FROM addresses;
    DELETE FROM telephones;
    DELETE FROM vendors;
    DELETE FROM shippers;
    DELETE FROM orders;
    DELETE FROM customers;
    
    sp_reset_keyvalue('customers');
    sp_reset_keyvalue('vendors');
    EXECUTE IMMEDIATE 'alter table orders modify order_id generated as identity ( start with 1)';
    EXECUTE IMMEDIATE 'alter table order_details modify orderdetail_id generated as identity ( start with 1)';
    EXECUTE IMMEDIATE 'alter table payments modify payment_id generated as identity ( start with 1)';
    EXECUTE IMMEDIATE 'alter table shippers modify shipper_id generated as identity ( start with 1)';    
    EXECUTE IMMEDIATE 'alter table inventory modify inventory_id generated as identity ( start with 1)';
    EXECUTE IMMEDIATE 'alter table addresses modify address_id generated as identity ( start with 1)';
    EXECUTE IMMEDIATE 'alter table telephones modify telephone_id generated as identity ( start with 1)';

    sp_load_shippers;
    sp_load_customers;
    sp_load_vendors;
    sp_load_addresses;    
    sp_load_telephone_numbers;   
    sp_load_orders;
	sp_load_inventory_items;
    sp_load_order_details;
    sp_load_payments;
    
    COMMIT WORK;
END;
/

CREATE OR REPLACE PROCEDURE sp_load_state_codes
AS
BEGIN
    Insert into state_codes values ('AK','Alaska');
    Insert into state_codes values ('AL','Alabama');
    Insert into state_codes values ('AR','Arkansas');
    Insert into state_codes values ('AZ','Arizona');
    Insert into state_codes values ('CA','California');
    Insert into state_codes values ('CO','Colorado');
    Insert into state_codes values ('CT','Connecticut');
    Insert into state_codes values ('DC','District Of Columbia');
    Insert into state_codes values ('DE','Delaware');
    Insert into state_codes values ('FL','Florida');
    Insert into state_codes values ('GA','Georgia');
    Insert into state_codes values ('HI','Hawaii');
    Insert into state_codes values ('IA','Iowa');
    Insert into state_codes values ('ID','Idaho');
    Insert into state_codes values ('IL','Illinois');
    Insert into state_codes values ('IN','Indiana');
    Insert into state_codes values ('KS','Kansas');
    Insert into state_codes values ('KY','Kentucky');
    Insert into state_codes values ('LA','Louisiana');
    Insert into state_codes values ('MA','Massachusetts');
    Insert into state_codes values ('ME','Maine');
    Insert into state_codes values ('MD','Maryland');
    Insert into state_codes values ('MI','Michigan');
    Insert into state_codes values ('MN','Minnesota');
    Insert into state_codes values ('MO','Missouri');
    Insert into state_codes values ('MS','Mississippi');
    Insert into state_codes values ('MT','Montana');
    Insert into state_codes values ('NC','North Carolina');
    Insert into state_codes values ('ND','North Dakota');
    Insert into state_codes values ('NE','Nebraska');
    Insert into state_codes values ('NH','New Hampshire');
    Insert into state_codes values ('NJ','New Jersey');
    Insert into state_codes values ('NM','New Mexico');
    Insert into state_codes values ('NV','Nevada');
    Insert into state_codes values ('NY','New York');
    Insert into state_codes values ('OH','Ohio');
    Insert into state_codes values ('OK','Oklahoma');
    Insert into state_codes values ('OR','Oregon');
    Insert into state_codes values ('PA','Pennsylvania');
    Insert into state_codes values ('PR','Puerto Rico');
    Insert into state_codes values ('RI','Rhode Island');
    Insert into state_codes values ('SC','South Carolina');
    Insert into state_codes values ('SD','South Dakota');
    Insert into state_codes values ('TN','Tennessee');
    Insert into state_codes values ('TX','Texas');
    Insert into state_codes values ('UT','Utah');
    Insert into state_codes values ('VT','Vermont');
    Insert into state_codes values ('VA','Virginia');
    Insert into state_codes values ('WA','Washington');
    Insert into state_codes values ('WI','Wisconsin');
    Insert into state_codes values ('WV','West Virginia');
    Insert into state_codes values ('WY','Wyoming');
    COMMIT WORK;
END;
/


