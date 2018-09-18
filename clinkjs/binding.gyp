{
	"targets": [
		{
			"target_name": "clink",
			"sources": [
				"clink.cc",
				"clink_wrap.cxx" 
			],
			"link_settings": {
				"libraries": [
					'-lserialport',
					'-lm',
					'-lpthread'
				],
				"library_dirs": [
					'/usr/local/lib',
				],

			}

		}
	]
}
