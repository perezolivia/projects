# My projects | Mis proyectos 🦋
Olivia's personal coding projects. | Proyectos personales de código de Olivia.
---
## ENGLISH INDEX 🇬🇧

   - [BMP photo editor](#editor-de-fotos-bmp)
  - [Conway's Game of Life](#juego-de-la-vida-de-conway)
  - [Sistema centralizado de expensas para consorcios](#sistema-centralizado-de-expensas-para-consorcios)
---
## ÍNDICE ESPAÑOL 🇦🇷
  - [Editor de fotos BMP](#editor-de-fotos-bmp)
  - [Juego de la vida de Conway](#juego-de-la-vida-de-conway)
  - [Sistema centralizado de expensas para consorcios](#sistema-centralizado-de-expensas-para-consorcios)

---

### Editor de fotos BMP
Esto es un editor de imágenes.

### Juego de la vida de Conway
Juego de la vida de Conway.

---
## `Sistema centralizado de expensas para consorcios`
### ✨ ¿Qué es?
Este proyecto es un sistema centralizado para una administración de consorcios que genera las expensas de cada consorcio de forma automatizada y mensual.

### 🌟 ¿Qué hace?
El sistema genera el documento de expensas de cada consorcio al quinto día hábil de cada mes y lo envía a la dirección de correo electrónico tanto del inquilino como del propietario.
Su **alcance** es:
  - [x] Dar de alta los departamentos y consorcios existentes con sus respectivos propietarios e inquilinos
  - [x] Importar los datos de los gastos ordinarios y extraordinarios por cada unidad habitacional del consorcio de los archivos correspondientes
  - [x] Calcular el estado financiero por consorcio y el estado de cuentas y prorrateo por unidad funcional, incluyendo saldos, ingresos, egresos, intereses y porcentajes a pagar
  - [x] Actualizar todos los datos anteriores en un documento informativo que conformará la expensa mensual a enviar.

### 💫 Habilidades utilizadas
Para poder conformar el sistema, se pasó por distintas áreas del ciclo de vida de un sistema:
#### Análisis de requisitos
- **Investigación sobre requerimientos técnicos y costo y modo de licenciamiento**
- **Presentación de un informe al cliente conteniendo los puntos clave** (software base, motor de base de datos recomendado, personal capacitado requerido, costo del soporte técnico del DBMS, costo de licencia, seguridad y cifrado ofrecidos sobre la información)
- **Investigación e informe sobre servicios alojados en la nube** (cálculos de costo en alternativas cloud, planteamiento de sistemas IaaS, PaaS y SaaS a conveniencia, estimación de inversión inicial y costo mensual de mantenimiento de una base de datos en la nube)
- **Investigación de términos, siglas, vocabulario y reglas de negocio pertenecientes al ámbito del sistema** (conceptos como CAPEX, OPEX, TCO, etc)

#### Diagramado y Diseñado de Sistemas
- **Realización de un DER que cumpla los requisitos del alcance.**

#### Implementación y Desarrollo del sistema
- **Instalación y documentación del DBMS a utilizar con su debida documentación correspondiente**
- **Creación de los objetos necesarios** (base de datos, tablas, vistas, stored procedures, funciones, triggers, etc) **para la importación de datos de los distintos tipos de archivos** (.csv, .xlsx, .txt, .json)
- **Normalización de datos**
- **Generación de reportes específicos mediante SP parametrizados, con informes XML para algunos de ellos**
- **Creación de índices para acelerar y optimizar consultas**
- **Incorporación de APIs como fuentes de datos externas**
- **Cifrado de datos sensibles/personales**
- **Creación de políticas de respaldo, programación de backups y RPO**

#### Pruebas / Testing
- **Creación de casos de prueba diversos que cumplan con los criterios de aceptación**
- **Revisión de documentos entregables y código fuente para asegurar su ajuste a las pautas**
- **Creación de scripts de testing ejecutables incluyendo los conjuntos de prueba**
- **Corrección de errores encontrados durante la fase de pruebas**

#### Lanzamiento, Despliegue y Mantenimiento
- **Corrección de errores, actualizaciones y adaptación del sistema a nuevas necesidades mediante el mantenimiento continuo.**

## 🌠 TL;DR: Conocimientos aplicados
- Análisis de requerimientos
- Redacción técnica
- Elaboración de DER
- Manipulado de SQL Server
- SQL: Creación de bases de datos, tablas (globales, en memoria, temporales, etc), stored procedures, vistas, triggers, funciones, índices, entre otros objetos. SQL, SQL dinámico y T-SQL. Importación de datos masivos de archivos JSON, .txt, .xlsx y .csv) usando ACE OLEDB. XML para presentar consultas. Incorporación de APIs externas con T-SQL. Creación de roles, usuarios y contraseñas. Encriptado de información sensible con hash.
- Manejo de sistemas de control de versiones como Git y su conexión a repositorios en GitHub
- Ejecución de conjuntos de prueba, testing funcional

### Documentación
La documentación detallada del proyecto se encuentra en el siguiente link.

### Nomenclatura y Estándares de Desarrollo

Para garantizar la coherencia y mantenibilidad del código T-SQL, se definieron las siguientes reglas de nomenclatura aplicadas a todos los objetos de la base de datos.

### 1. Convenciones Generales

* **Idioma:** Español (se evita el uso de ñ y tildes en nombres de objetos para compatibilidad).
* **Case:** `snake_case` (minúsculas separadas por guiones bajos).
* **Singular/Plural:**
    * **Tablas:** Nombres en **singular** (ej. `unidad_funcional`, `pago`).
    * **Esquemas:** Sustantivos en **plural** o colectivos (ej. `consorcios`, `finanzas`).

### 2. Prefijos y Definiciones

| Objeto de Base de Datos | Prefijo / Formato | Descripción | Ejemplo |
| :--- | :--- | :--- | :--- |
| **Primary Key (PK)** | `id_` + [entidad] | Identificador único numérico o compuesto. | `id_consorcio` |
| **Foreign Key (FK)** | `id_` + [entidad] | Referencia a la PK de otra tabla. | `id_expensa` |
| **Stored Procedures** | `sp_` + [verbo] | Procedimientos almacenados para lógica de negocio. | `sp_generar_cuotas` |
| **Funciones** | `fn_` + [utilidad] | Funciones escalares o de tabla para transformación de datos. | `fn_normalizar_monto` |
| **Índices** | `IX_` + [tabla] + [cols] | Índices no agrupados para optimización de consultas. | `IX_pago_fecha` |
| **Variables** | `@` + [nombre] | Variables locales y parámetros (camelCase o snake_case). | `@fecha_hasta` |

### 3. Organización de Esquemas

La base de datos se estructura en esquemas lógicos para separar dominios de negocio:

| Esquema | Propósito | Tablas Principales |
| :--- | :--- | :--- |
| **`consorcios`** | Datos estructurales de los inmuebles. | `consorcio`, `unidad_funcional` |
| **`personas`** | Gestión de entidades legales y físicas. | `persona`, `rol`, `proveedor` |
| **`finanzas`** | Núcleo transaccional y contable. | `pago`, `expensa`, `gasto_ordinario`, `cuota` |
| **`gestion`** | Procesos administrativos y comunicación. | `envio_expensa`, `tipo_envio` |
| **`datos`** | Capa de reporting y análisis de negocio. | (Contiene solo Stored Procedures de reporte) |
| **`utils`** | Herramientas de sistema e importación. | (Scripts de carga masiva y funciones auxiliares) |

### Organización del proyecto
Se realizaron siete entregas distintas del proyecto. 
#### Entrega 1
Se estableció un escenario hipotético en el que el cliente dispone de un servidor con determinadas capacidades y el equipo debió analizar si estas eran suficientes para alojar el motor de base de datos OracleDB.
#### Entrega 2
Se analizó la posibilidad de alojar la base de datos en la nube, contando con 3 alternativas: GCP, AWS y Microsoft Azure. 
#### Entrega 3
Se diseñó el DER para almacenar la información requerida para la gestión de las expensas de un consorcio. 
#### Entrega 4
Se generó el documento de instalación para la base de datos. 
#### Entrega 5
Se realizó la importación de los archivos que contienen la información relacionada a los consorcios y las unidades funcionales.
#### Entrega 6 
Se generó una serie de reportes requeridos. 
#### Entrega 7
Se establecieron políticas de seguridad como la creación de usuarios y roles específicos, así como también se realizó la encriptación de datos personales y/o sensibles.

### ⚠ IMPORTANTE: Instalación
Para trabajar con este proyecto se necesita contar con los siguientes componentes instalados:

#### 1. SQL Server
Se requiere una instancia de Microsoft SQL Server (versión 2016 o superior).
Se recomienda la versión Express (gratuita, con limitaciones de recursos pero útil para un pequeño proyecto)

Descargar: https://www.microsoft.com/en-us/sql-server/sql-server-downloads

#### 2. SQL Server Management Studio (SSMS)

Cliente gráfico utilizado para administrar la base de datos, ejecutar scripts y gestionar objetos SQL Versión recomendada: SSMS 19.x o superior

Descargar: https://learn.microsoft.com/sql/ssms/download-sql-server-management-studio

#### 3. Microsoft Access Database Engine (ACE OLEDB)
Necesario para la importación de archivos Excel (.xlsx, .xls) desde SQL Server mediante OPENROWSET u OPENQUERY. Debe coincidir la instalación de ACE con la arquitectura de SQL Server (32 o 64 bits).

Descargar: https://www.microsoft.com/en-us/download/details.aspx?id=54920

#### 4. Permisos necesarios
Asegúrate de que el usuario SQL utilizado tenga permisos para:

Crear bases de datos.
Crear tablas, vistas, SPs y funciones.

Ejecutar OPENROWSET y BULK INSERT.


  



