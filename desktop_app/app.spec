# -*- mode: python ; coding: utf-8 -*-

block_cipher = None

# Include pyserial as a hidden import
hidden_imports = ['pyserial','pyqt5','time', 'sys']

a = Analysis(['ambilight_V2.py'],
             pathex=[''],
             binaries=[],
             datas=[],
             hiddenimports=hidden_imports,
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher,
             noarchive=False)

pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)

exe = EXE(pyz,
          a.scripts,
        a.binaries,
          a.zipfiles,
          a.datas,
          [],
          exclude_binaries=True,
          name='Ambilight_V2',
          debug=False,
          bootloader_ignore_signals=False,
          strip=False,
          upx=True,
          console=False,
          icon='icon.ico',
          oneFile=True)

coll = COLLECT(exe,
               a.binaries,
               a.zipfiles,
               a.datas,
               strip=False,
               upx=True,
               upx_exclude=[],
               name='Ambilight_V2')
