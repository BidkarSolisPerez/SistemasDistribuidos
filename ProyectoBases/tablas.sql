CREATE TABLE
IF NOT EXISTS estudiante
(   id_estudiante INT,
    nombre TEXT,
    edad INT,
    email TEXT,
    phone TEXT
);

CREATE TABLE
IF NOT EXISTS profesor
(
    id_profesor INT,
    nombre TEXT,
    grado_academico TEXT,
    email TEXT,
    telefono TEXT
);

CREATE TABLE
IF NOT EXISTS curso
(
    id_curso INT,
    nombre_curso TEXT,
    nombre_coordinador TEXT,
    ciclo_disponible INT,
    creditos INT
);

CREATE TABLE
IF NOT EXISTS escuela
(
    id_escuela INT,
    nombre_escuela TEXT,
    nombre_director TEXT,
    facultad_pertenece TEXT
);