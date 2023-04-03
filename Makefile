build:
	make build -C memory

debug:
	make debug -C memory

clean:
	make clean -C shared
	make clean -C memory

# # Esto tambien borra todos los archivos de log y el FS de mongus
# recontra:
# 	make clean
# 	make limpiar_fs -C i_mongo_store
# 	find . -name "*.log" -type f -delete