# src/python/util.py
#
# Utility methods.
#
# Since:
#     2019-02-15
__version__="2019-02-15"
__authors__=["Michael Federczuk","Riedler"]

#importing modules
import pyaudio, wave

#author: Michael Federczuk
def join_root(*paths):
	from game import root_path
	import os
	full_path = root_path
	for path in paths:
		full_path = os.path.join(full_path, path)
	#end for
	return full_path
#end def

#author: Michael Federczuk
def join_assets(*paths):
	from game import assets_path
	import os
	full_path = assets_path
	for path in paths:
		full_path = os.path.join(full_path, path)
	#end for
	return full_path
#end def

#author: Riedler
class audio():
	def __init__(self,loop=False):
		self.p=pyaudio.PyAudio()
		self.loop=loop
	#@param f: Absoluter Pfad zur Audiodatei (wave only)
	#@param bufsize: Größe des Buffers
	def play(self,f,bufsize=2048):
		try:
			self.wf = wave.open(f,'rb')
			self.stream=self.p.open(format=self.p.get_format_from_width(self.wf.getsampwidth()),channels=self.wf.getnchannels(),rate=self.wf.getframerate(),output=True,stream_callback=self.callback,frames_per_buffer=bufsize)
			self.stream.start_stream()
		except Exception as e:
			exc=e
		else:
			exc=None
		return (self.wf,self.stream,self.p,exc)
	def callback(self,in_data, frame_count, time_info, status):
		return (self.wf.readframes(frame_count), pyaudio.paContinue)
	#@param wait: if True, waits for file to finish
	def close(self,wait=False):
		try:
			while wait==True and self.stream.is_active():
				time.sleep(0.1)
			self.stream.stop_stream()
			self.stream.close()
			self.p.terminate()
			self.wf.close()
		except Exception as e:
			return e
