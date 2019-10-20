CREATE TABLE
IF NOT EXISTS estudiante
(   id_estudiante INT,
    nombre TEXT,
    edad INT,
    email TEXT,
    phone TEXT
);

INSERT into estudiante
values
    (1325, "Juan Mora", 20, "j.mora@univ.ac.cr", "50685649578");
INSERT into estudiante
values
    (1659, "Pedro Moya", 23, "p.moya@univ.ac.cr", "50685649578");
INSERT into estudiante
values
    (2134, "Laura Montiel", 23, "L.montiel@univ.ac.cr", "50685649578");
INSERT into estudiante
values
    (3654, "Monica Fernandez", 21, "j.moya@univ.ac.cr", "50685649578");
INSERT into estudiante
values
    (2564, "Jose Solis", 23, "j.solis@univ.ac.cr", "50685649578");

CREATE TABLE
IF NOT EXISTS profesor
(
    id_profesor INT,
    nombre TEXT,
    grado_academico TEXT,
    email TEXT,
    telefono TEXT
);

INSERT into profesor
values
    (1, "Carlos Vargas", "Msc", "j.vargas@univ.ac.cr", "50685649578");
INSERT into profesor
values
    (2, "Jose Calvo", "Lic", "j.vargas@univ.ac.cr", "50685649578");
INSERT into profesor
values
    (3, "Manuel Castro", "Lic", "j.vargas@univ.ac.cr", "50685649578");
INSERT into profesor
values
    (4, "Silvia Mora", "Phd", "j.vargas@univ.ac.cr", "50685649578");
INSERT into profesor
values
    (5, "Juan Solis", "Msc", "j.vargas@univ.ac.cr", "50685649578");

CREATE TABLE
IF NOT EXISTS curso
(
    id_curso INT,
    nombre_curso TEXT,
    nombre_coordinador TEXT,
    ciclo_disponible INT,
    creditos INT
);

INSERT into curso
values
    (1, "Estructura de datos", "Eddy Ramirez", 2, 3);
INSERT into curso
values
    (2, "Programacion web", "George Martinez", 1, 3);
INSERT into curso
values
    (3, "Sistemas Distribuidos", "Armando Arce", 2, 3);
INSERT into curso
values
    (4, "Sistemas Operativos", "Eddy Ramirez", 2, 3);
INSERT into curso
values
    (5, "Paradigmas de programacion", "Carlos Loria", 2, 3);

CREATE TABLE
IF NOT EXISTS escuela
(
    id_escuela INT,
    nombre_escuela TEXT,
    nombre_director TEXT,
    facultad_pertenece TEXT
);

INSERT into escuela
values
    (1, "Informatica", "Jhonny Villalobosz", "Ciencias exactas y naturales");
INSERT into escuela
values
    (2, "Negocios", "Carlos Mora", "Ciencias Sociales");
INSERT into escuela
values
    (3, "Ingles", "Jhon Brown", "Ciencias Sociales");
INSERT into escuela
values
    (4, "Educacion", "Jose Porras", "Ciencias sociales");
INSERT into escuela
values
    (5, "Quimica", "Michael Smoch", "Ciencias exactas y naturales");
    


