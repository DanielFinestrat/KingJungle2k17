ESTOY EDITANDO
# King of the Jungle 2k17: Turbo Power Edition
# Instrucciones de configuración del repositorio en Ubuntu y Windows(Consola de comandos):

1.- Descargar Git (En windows descargar de la Web): 

  - ```sudo apt-get install git```

2.- Configurar nombre y correo (En Windows desde la aplicación de escritorio):

  - ```sudo git config --global user.name "miNombre"```

  - ```sudo git config --global user.email "miEmail@miDominio.com"```

3.- Navegar a la carpeta y clonar nuestro repositorio (En Windows desde la aplicación de escritorio):

  - ```git clone https://github.com/DanielFinestrat/MiniServidorHTTP```

4.- Editar, y al terminar usar (En Windows desde la GitHub Shell usando los mismos comandos):

- Para añadir los cambios (Todos los archivos):

  - ```git add -A```

- Para añadir los cambios (Solo algunos archivos específicos):

  - ```git add nombreArchivo```

- Para ponerle un mensaje a la actualziación:

  - ```git commit -m "Mensaje de Actualziación"```

- Para subirlo a la rama (te pedira tus datos de usuario de GitHub, introdúcelos):

  - ```git push```

5.- Si regresamos después de un tiempo, para actualizar nuestro clon usar:

  - ```git pull```

6.- Si queremos descartar cambios sin subirlos:

  - ```git reset --hard HEAD```
  - ```git pull```
